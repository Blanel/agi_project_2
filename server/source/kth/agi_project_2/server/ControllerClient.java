/**
 * Handles communication with controller clients
 * @author Eric Nellåker
 */
package kth.agi_project_2.server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.StringReader;
import java.net.Socket;
import java.util.Random;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;


import org.w3c.dom.Attr;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

public class ControllerClient implements Runnable{

	// Player variables
	private Airplane plane;
	private boolean isShooting;
	private double rotation;
	private double speedMod;
	private int cachedLife;
	
	// Connection variables
	private Socket sock;
	private InputStream is;
	private OutputStream os;
	private BufferedReader br;
	private InputStreamReader isr;
	
	// Server Variables
	private GameState gs;
	
	// Threading
	private Thread timeoutThread;
	private Thread pingThread;
	private boolean shuttingDown;
	private static final long PING = 1000;
	private static final long TIMEOUT =15000; 

	public ControllerClient(Socket soc, GameState gs) throws IOException
	{
		this.gs = gs;
		this.sock = soc;
		
		is = soc.getInputStream();
		isr = new InputStreamReader(is);
		os = soc.getOutputStream();
		br = new BufferedReader(isr);
		
		shuttingDown = false;
		isShooting = false;
		rotation = 0;
		plane=null;

		// Checks to see if Controller Client has taken abnormally long time to respond, and kills the connection in that case
		timeoutThread = new Thread()
		{
			public void run()
			{

				while(!sock.isClosed())
				{
					try {
						sleep(TIMEOUT);
						shutDown();
						System.err.println("Controller Client timed out!");
					} catch (InterruptedException e) {
						// Do nothing!
					}
				}
			}
		};
		
		// Sends a packet to the Controller Client, just to make sure it knows we love it.
		pingThread = new Thread()
		{
			public void run()
			{
				while(!sock.isClosed())
				{
					try
					{
						sleep(PING);
						sendEvents(true);

					}
					catch(InterruptedException e)
					{
						// Do nothing
					}
				}
			}
		};
	}
	
	/**
	 * Checks all the variables set by the Controller Client and updates the gamestate to reflect this.
	 */
	public void update()
	{
		if(plane != null)
		{
			plane.addAngle(rotation*0.002);
			plane.speedMod(speedMod);
			if(isShooting)
			{
				gs.bullets.add(new Bullet(gs.nextBId(), plane, gs));
				isShooting=false;
			}
		}
	}

	/**
	 * Runs the thread keeping track of everything to do with the Controller Client and its plane.
	 */
	public void run() {
		timeoutThread.start();
		pingThread.start();
		while(!sock.isClosed())
		{
			// Read in a line
			String line=null;
			try {
				if(br.ready())
				{
					line = br.readLine();
				}
			} catch (IOException e2) {
				System.err.println("IOException when reading line!");
				shutDown();
			}

			// Is the line read sane?
			if(line!=null && line.startsWith("<?xml") && line.endsWith("</Controller ClientClient>") )
			{
				//System.err.println(line);
				// In that case, interrupt the timeout thread (as we have gotten a response) and parse the line.
				timeoutThread.interrupt();
				try {
					DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
					DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
					Document doc = docBuilder.parse(new InputSource(new StringReader(line)));

					// If plane is null, check if there exists a plane with the given ID, else create a new plane. (This is for reconnecting)
					if(plane==null)
					{
						int id = Integer.parseInt(doc.getElementsByTagName("id").item(0).getTextContent());
						Coord centre = gs.getCentre();
						double angle = new Random().nextDouble()*Math.PI*2;
						if(id == -1)
						{
							System.out.println("New Plane created!");
							plane = new Airplane(gs.nextAId(),centre.x+Math.cos(angle+Math.PI), centre.y+Math.sin(angle+Math.PI),angle, gs);
							gs.airplanes.add(plane);
						}
						else
						{
							plane = gs.getPlaneById(id);
							if(plane == null)
							{
								System.out.println("New Plane created!");
								plane = new Airplane(gs.nextAId(),centre.x+Math.cos(angle+Math.PI), centre.y+Math.sin(angle+Math.PI),angle, gs);
								gs.airplanes.add(plane);
							}
							else
							{
								System.out.println("Reconnect Succesful!");
							}
						}
						cachedLife = plane.getLife();
					}
					
					// Check the usual stuff, like rotation and is he shooting and stuff.
					rotation = Double.parseDouble(doc.getElementsByTagName("rotation").item(0).getTextContent());
					isShooting = Boolean.parseBoolean(doc.getElementsByTagName("shooting").item(0).getTextContent());
					speedMod = Double.parseDouble(doc.getElementsByTagName("speedmod").item(0).getTextContent());
				} catch ( IOException e) {
					System.err.println("Something went catostrophacally wrong while recieving data (IO)! Disconnecting Controller Client...");
					shutDown();
				} catch (ParserConfigurationException | SAXException e) {
					System.err.println("Something went catostrophacally wrong while recieving data (Parser)! Disconnecting Controller Client...");
					shutDown();
				}

			}
			else
			{
				if(line != null)
					System.err.println(line);
			}
			try {
				Thread.sleep(70);
			} catch (InterruptedException e) {
				// Do nothing
			}
		}

	}

	/**
	 * Send stuff to Controller Client.
	 * @param ping If true, doesn't interrupt the ping thread (as it was the ping thread that started the event) 
	 */
	public void sendEvents(boolean ping)
	{
		if(plane!=null && ((plane.getLife()<cachedLife) || ping))
		{
			if(!ping)
			{
				pingThread.interrupt();
			}
			cachedLife = plane.getLife();
			
			// Send hit info to Controller Client
			try {
				DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
				DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
				Document doc = docBuilder.newDocument();

				Element rootElement = doc.createElement("Controller ClientResponse");
				doc.appendChild(rootElement);
				Attr ts = doc.createAttribute("ts");
				ts.setValue(""+System.currentTimeMillis());
				rootElement.setAttributeNode(ts);

				Element idTag = doc.createElement("id");
				rootElement.appendChild(idTag);
				idTag.appendChild(doc.createTextNode(""+plane.getId()));

				Element lifeTag = doc.createElement("life");
				rootElement.appendChild(lifeTag);
				lifeTag.appendChild(doc.createTextNode(""+plane.getLife()));

				TransformerFactory transformerFactory = TransformerFactory.newInstance();
				Transformer transformer = transformerFactory.newTransformer();
				DOMSource source = new DOMSource(doc);

				StreamResult result = new StreamResult(os);
				transformer.transform(source,result);
				os.write("\n".getBytes());
				os.flush();

			} catch (ParserConfigurationException | TransformerException e1) {
				System.err.println("Something went catostrophacally wrong while sending data (Parser)! Disconnecting Controller Client...");
				shutDown();
				return;
			} catch (IOException e) {
				System.err.println("Something went catostrophacally wrong while sending data (IO)! Disconnecting Controller Client...");
				shutDown();
				return;
			}

			if(plane.getLife()<=0)
			{
				shutDown();
			}
		}
	}

	public boolean isOpen()
	{
		return !sock.isClosed();
	}
	public Socket getSocket()
	{
		return sock;
	}

	public boolean shutDown()
	{
		if(!shuttingDown)
		{
			System.err.println("Shutdown started!");
			shuttingDown=true;
			try
			{
				br.close();
				isr.close();
				is.close();
				os.close();
				sock.close();
				timeoutThread.interrupt();
			}
			catch(IOException e)
			{
				shuttingDown=false;
				System.err.println("Shutdown failed!");
				e.printStackTrace();
				return false;
			}
			shuttingDown = false;
			System.err.println("Shutdown success!");
			return true;
		}
		System.err.println("Shutdown already in progress!");
		return false;
	}
}
