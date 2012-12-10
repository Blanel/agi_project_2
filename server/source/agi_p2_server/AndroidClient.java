package agi_p2_server;

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

public class AndroidClient implements Runnable{

	private Airplane plane;
	private Socket sock;
	private boolean isShooting;
	//private boolean hasShot;
	private double rotation;
	private double speedMod;
	private InputStream is;
	private OutputStream os;
	private BufferedReader br;
	private InputStreamReader isr;
	private GameState gs;
	private int cachedLife;
	private Thread timeoutThread;
	private Thread pingThread;
	private static final long PING = 1000;
	private static final long TIMEOUT =10000; 


	public AndroidClient(Socket soc, GameState gs) throws IOException
	{

		this.sock = soc;
		is = soc.getInputStream();
		isr = new InputStreamReader(is);
		os = soc.getOutputStream();
		br = new BufferedReader(isr);
		this.gs = gs;

		isShooting = false;
		//hasShot = false;
		rotation = 0;
		//double angle = new Random().nextDouble()*Math.PI*2;
		//Coord centre = gs.getCentre();
		
		plane=null;
		//plane = new Airplane(gs.nextAId(),centre.x+Math.cos(angle+Math.PI), centre.y+Math.sin(angle+Math.PI),angle);
		//gs.airplanes.add(plane);
		//cachedLife = plane.getLife();

		timeoutThread = new Thread()
		{
			public void run()
			{

				while(!sock.isClosed())
				{
					try {
						sleep(TIMEOUT);
						shutDown();
						System.err.println("Android timed out!");
					} catch (InterruptedException e) {
						// Do nothing!
					}
				}
			}
		};
		
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
						
					}
				}
			}
		};
	}

	public void update()
	{
		if(plane != null)
		{
		plane.addAngle(rotation*0.001);
		plane.speedMod(speedMod);
		if(isShooting)
		{
			gs.bullets.add(new Bullet(gs.nextBId(), plane));
			isShooting=false;
		}
		}

	}


	public void run() {
		timeoutThread.start();
		pingThread.start();
		while(!sock.isClosed())
		{


			String line=null;
			
			try {
				line = br.readLine();
			} catch (IOException e2) {
				System.err.println("IOException when reading line!");
				shutDown();
			}
			if(line!=null && line.startsWith("<?xml") && line.endsWith("</androidClient>") )
			{
				timeoutThread.interrupt();
				try {
					DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
					DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
					Document doc = docBuilder.parse(new InputSource(new StringReader(line)));
					//Document doc = docBuilder.parse(line);
					if(plane==null)
					{
						int id = Integer.parseInt(doc.getElementsByTagName("id").item(0).getTextContent());
						Coord centre = gs.getCentre();
						double angle = new Random().nextDouble()*Math.PI*2;
						if(id == -1)
						{
							System.out.println("New Plane created!");
							plane = new Airplane(gs.nextAId(),centre.x+Math.cos(angle+Math.PI), centre.y+Math.sin(angle+Math.PI),angle);
							gs.airplanes.add(plane);
						}
						else
						{
							plane = gs.getPlaneById(id);
							if(plane == null)
							{
								System.out.println("New Plane created!");
								plane = new Airplane(gs.nextAId(),centre.x+Math.cos(angle+Math.PI), centre.y+Math.sin(angle+Math.PI),angle);
								gs.airplanes.add(plane);
							}
							else
							{
								System.out.println("Reconnect Succesful!");
							}
						}
						cachedLife = plane.getLife();
					}
					rotation = Double.parseDouble(doc.getElementsByTagName("rotation").item(0).getTextContent());
					isShooting = Boolean.parseBoolean(doc.getElementsByTagName("shooting").item(0).getTextContent());




				} catch ( IOException e) {
					System.err.println("Something went catostrophacally wrong while recieving data (IO)! Disconnecting android...");
					shutDown();
				} catch (ParserConfigurationException | SAXException e) {
					System.err.println("Something went catostrophacally wrong while recieving data (Parser)! Disconnecting android...");
					shutDown();
				}

			}
			else
			{
				if(line != null)
					System.err.println(line);
			}
		}

	}


	public void sendEvents(boolean forced)
	{
		//System.err.println("StuffSent");
		
			
		if(plane!=null && ((plane.getLife()<cachedLife) || forced))
		{
			if(!forced)
			{
				pingThread.interrupt();
			}
			//System.err.println("Sending packet to android...");
			cachedLife = plane.getLife();
			// Send hit info to android
			try {
				DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
				DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
				Document doc = docBuilder.newDocument();

				Element rootElement = doc.createElement("androidResponse");
				doc.appendChild(rootElement);
				Attr ts = doc.createAttribute("ts");
				ts.setValue(""+System.currentTimeMillis());
				rootElement.setAttributeNode(ts);
				
				Attr id = doc.createAttribute("id");
				id.setValue(""+plane.getId());
				rootElement.setAttributeNode(id);
				
				
				
				
				
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
				System.err.println("Something went catostrophacally wrong while sending data (Parser)! Disconnecting android...");
				//e1.printStackTrace();
				shutDown();
				return;
			} catch (IOException e) {
				System.err.println("Something went catostrophacally wrong while sending data (IO)! Disconnecting android...");
				shutDown();
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
		System.err.println("Shutdown started!");
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
			System.err.println("Shutdown failed!");
			e.printStackTrace();
			return false;
		}
		System.err.println("Shutdown success!");
		return true;
	}

}
