package agi_p2_server;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.StringReader;
import java.net.Socket;
import java.util.Random;
import java.util.Scanner;

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
	private Socket soc;
	private boolean isShooting;
	private double rotation;
	private double speedMod;
	private InputStream is;
	private OutputStream os;
	private Scanner sc;
	private GameState gs;
	private int cachedLife;
	
	
	public AndroidClient(Socket soc, GameState gs) throws IOException
	{
		
		this.soc = soc;
		is = soc.getInputStream();
		os = soc.getOutputStream();
		sc = new Scanner(is);
		
		isShooting = false;
		rotation = 0;
		double angle = new Random().nextDouble()*Math.PI*2;
		Coord centre = gs.getCentre();
		plane = new Airplane(gs.nextAId(),centre.x+Math.cos(angle+Math.PI), centre.y+Math.sin(angle+Math.PI),angle);
		gs.airplanes.add(plane);
		cachedLife = plane.getLife();
	}
	
	public void update()
	{
		plane.addAngle(rotation);
		plane.speedMod(speedMod);
		if(isShooting)
		{
			gs.bullets.add(new Bullet(gs.nextBId(), plane));
			isShooting=false;
		}

	}

	
	public void run() {
		while(!soc.isClosed())
		{
			if(sc.hasNextLine())
			{
				String line = sc.nextLine();
				//System.err.println(line);
				try {
					DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
					DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
					Document doc = docBuilder.parse(new InputSource(new StringReader(line)));
					//Document doc = docBuilder.parse(line);
					rotation = Double.parseDouble(doc.getElementsByTagName("rotation").item(0).getTextContent());
					if(!isShooting)
						isShooting = Boolean.parseBoolean(doc.getElementsByTagName("shooting").item(0).getTextContent());
					
				} catch (ParserConfigurationException  | IOException e) {
					System.err.println("Something went catostrophacally wrong while recieving data! Disconnecting android...");
					try {
						soc.close();
					} catch (IOException e1) {
						System.err.println("an IO derp");
					}
					return;
				} catch (SAXException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

				
			}
		}
	}

	
	public void sendEvents()
	{
		if(plane.getLife()<cachedLife)
		{
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
				
				Element lifeTag = doc.createElement("life");
				rootElement.appendChild(lifeTag);
				lifeTag.appendChild(doc.createTextNode(""+plane.getLife()));
				
				TransformerFactory transformerFactory = TransformerFactory.newInstance();
				Transformer transformer = transformerFactory.newTransformer();
				DOMSource source = new DOMSource(doc);
				
				StreamResult result = new StreamResult(os);
				transformer.transform(source,result);
				os.write("\n".getBytes());
			
			} catch (ParserConfigurationException | TransformerException e1) {
				System.err.println("Something went catostrophacally wrong while sending data! Disconnecting android...");
				try {
					soc.close();
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
					soc.close();
				} catch (IOException e) {
					System.err.println("an IO derp");
				}
			}
		}
			
	}
	
	public boolean isOpen()
	{
		return !soc.isClosed();
	}
	public Socket getSocket()
	{
		return soc;
	}
	

}
