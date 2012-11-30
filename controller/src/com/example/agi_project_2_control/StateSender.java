package com.example.agi_project_2_control;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.StringReader;
import java.net.Socket;
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

public class StateSender {
	
	private double speedFrac;
	private int screenHeight;
	private boolean shooting;
	private float rotX;
	private float rotY;
	private Socket soc;
	private MainActivity ma;
	private OutputStream os;
	private InputStream is;
	
	private final static long INTERVALL=40;
	
	public StateSender(MainActivity m)
	{
		ma = m;
		speedFrac = 0;
		shooting = false;
		screenHeight = 1;
		rotX = 0;
		rotY = 0;
	}
	public Socket getSoc() {
		return soc;
	}
	public void setSoc(Socket soc) throws IOException {
		this.soc = soc;
		is = soc.getInputStream();
		os = soc.getOutputStream();
	}
	public StateSender(MainActivity m, Socket soc) throws IOException
	{
		ma = m;
		setSoc(soc);
		speedFrac = 0;
		shooting = false;
		screenHeight = 1;
		rotX = 0;
		rotY = 0;
	}
	
	public StateSender(MainActivity m, Socket soc, int h) throws IOException
	{
		ma = m;
		setSoc(soc);
		speedFrac = 0;
		shooting = false;
		screenHeight = h;
		rotX = 0;
		rotY = 0;
	}
	
	
	private double getRotation()
	{
		return -((Math.atan2(rotX, rotY)+Math.PI/2)*10/Math.PI);
	}
	public void startListenerThreads()
	{
		//Server Listener
		(new Thread()
		{
			public void run()
			{
				Scanner sc = new Scanner(is);
				while(!soc.isClosed())
				{
					if(sc.hasNextLine())
					{
						String line = sc.nextLine();

						try {
							DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
							DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
							Document doc = docBuilder.parse(new InputSource(new StringReader(line)));
							ma.airplane.setLife(Integer.parseInt(doc.getElementsByTagName("life").item(0).getTextContent()));
							ma.lifeSpan();
						} catch (IOException e) {
							System.err.println("Something went catostrophacally wrong while recieving data! Disconnecting android...");
							try {
								soc.close();
							} catch (IOException e1) {
								System.err.println("an IO derp");
							}
							return;
						} catch (SAXException e) {
							System.err.println("Something went catostrophacally wrong while recieving data! Disconnecting android...");
							try {
								soc.close();
							} catch (IOException e1) {
								System.err.println("an IO derp");
							}
							return;
						} catch (ParserConfigurationException e) {
							System.err.println("Something went catostrophacally wrong while recieving data! Disconnecting android...");
							try {
								soc.close();
							} catch (IOException e1) {
								System.err.println("an IO derp");
							}
							return;
						}


					}
				}
			}
		}).start();
		//Server Sender
		(new Thread()
		{
			public void run()
			{
				while(true) // TODO Create sane operation here
				{
					// Send hit info to android
					try {
						DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
						DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
						Document doc = docBuilder.newDocument();

						Element rootElement = doc.createElement("androidClient");
						doc.appendChild(rootElement);
						Attr ts = doc.createAttribute("ts");
						ts.setValue(""+System.currentTimeMillis());
						rootElement.setAttributeNode(ts);

						Element rotationTag = doc.createElement("rotation");
						rootElement.appendChild(rotationTag);
						rotationTag.appendChild(doc.createTextNode(""+getRotation()));

						Element shootingTag = doc.createElement("shooting");
						rootElement.appendChild(shootingTag);
						shootingTag.appendChild(doc.createTextNode(""+shooting));
						
						Element speedmodTag = doc.createElement("speedmod");
						rootElement.appendChild(speedmodTag);
						speedmodTag.appendChild(doc.createTextNode(""+speedFrac));
						
						TransformerFactory transformerFactory = TransformerFactory.newInstance();
						Transformer transformer = transformerFactory.newTransformer();
						DOMSource source = new DOMSource(doc);

						StreamResult result = new StreamResult(os);
						transformer.transform(source,result);
						os.write("\n".getBytes());

					} catch (ParserConfigurationException e1) {
						System.err.println("Something went catostrophacally wrong while sending data! Disconnecting android...");
						try {
							soc.close();
						} catch (IOException e) {
							System.err.println("an IO derp");
						}
						return;
					} catch (TransformerException e1) {
						System.err.println("Something went catostrophacally wrong while sending data! Disconnecting android...");
						try {
							soc.close();
						} catch (IOException e) {
							System.err.println("an IO derp");
						}
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}


					
				}
			}
		}).start();
	}
	

	public double getSpeedFrac() {
		return speedFrac;
	}

	public void setSpeedFrac(double speedFrac) {
		this.speedFrac = speedFrac;
	}

	public int getScreenHeight() {
		return screenHeight;
	}

	public void setScreenHeight(int screenHeight) {
		this.screenHeight = screenHeight;
	}

	public boolean isShooting() {
		return shooting;
	}

	public void setShooting(boolean shooting) {
		this.shooting = shooting;
	}

	public float getRotX() {
		return rotX;
	}

	public void setRotX(float rotX) {
		this.rotX = rotX;
	}

	public float getRotY() {
		return rotY;
	}

	public void setRotY(float rotY) {
		this.rotY = rotY;
	}
	
	
	
	

}
