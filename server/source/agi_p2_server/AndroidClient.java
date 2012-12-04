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
		double angle = new Random().nextDouble()*Math.PI*2;
		Coord centre = gs.getCentre();
		plane = new Airplane(gs.nextAId(),centre.x+Math.cos(angle+Math.PI), centre.y+Math.sin(angle+Math.PI),angle);
		gs.airplanes.add(plane);
		cachedLife = plane.getLife();

		timeoutThread = new Thread()
		{
			public void run()
			{

				while(!sock.isClosed())
				{
					try {
						sleep(TIMEOUT);
						sock.close();
					} catch (InterruptedException | IOException e) {
						// Do nothing!
					}
				}
			}
		};
	}

	public void update()
	{
		plane.addAngle(rotation*0.001);
		plane.speedMod(speedMod);
		if(isShooting)
		{
			gs.bullets.add(new Bullet(gs.nextBId(), plane));
			isShooting=false;
		}

	}


	public void run() {
		timeoutThread.start();
		while(!sock.isClosed())
		{


			String line=null;
			
			try {

				line = br.readLine();
			} catch (IOException e2) {
				// TODO Auto-generated catch block
				System.err.println("IOException when reading line!");
				e2.printStackTrace();

				System.err.println(sock.isClosed());
				try {
					sock.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				//is.
				//e2.printStackTrace();
				
			}
			
			if(line!=null && line.startsWith("<?xml") && line.endsWith("</androidClient>") )
			{
				timeoutThread.interrupt();
				//System.err.println(line);
				try {
					DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
					DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
					Document doc = docBuilder.parse(new InputSource(new StringReader(line)));
					//Document doc = docBuilder.parse(line);
					rotation = Double.parseDouble(doc.getElementsByTagName("rotation").item(0).getTextContent());
					isShooting = Boolean.parseBoolean(doc.getElementsByTagName("shooting").item(0).getTextContent());




				} catch ( IOException e) {
					System.err.println("Something went catostrophacally wrong while recieving data! Disconnecting android...");
					try {
						sock.close();
					} catch (IOException e1) {
						System.err.println("an IO derp");
					}
					return;
				} catch (ParserConfigurationException | SAXException e) {
					System.err.println(line);

				}

			}
			else
			{
				if(line != null)
					System.err.println(line);
				//is.
			}
		}

	}


	public void sendEvents()
	{
		//System.err.println("StuffSent");
		if(plane.getLife()<cachedLife)
		{
			System.err.println("Sending packet to android...");
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
				System.err.println("Something went catostrophacally wrong while sending data! Disconnecting android...");
				//e1.printStackTrace();
				try {
					sock.close();
				} catch (IOException e) {
					System.err.println("an IO derp");
				}
				return;
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}


			if(plane.getLife()<=0)
			{
				try {
					sock.close();
				} catch (IOException e) {
					System.err.println("an IO derp");
				}
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


}
