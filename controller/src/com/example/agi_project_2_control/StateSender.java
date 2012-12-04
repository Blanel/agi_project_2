package com.example.agi_project_2_control;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
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

import android.os.Message;

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
	private InputStreamReader isr;
	private BufferedReader br;
	
	private int cachedLife = 5;
	private int life = 5;
	
	private int id = -1;

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
		isr = new InputStreamReader(is);
		br = new BufferedReader(isr);
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

				while(!soc.isClosed())
				{

					

					try {
						String line = br.readLine();
						DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
						DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
						Document doc = docBuilder.parse(new InputSource(new StringReader(line)));
						setLife(Integer.parseInt(doc.getElementsByTagName("life").item(0).getTextContent()));
					} catch (IOException e1) {
						System.err.println("Something went catostrophacally wrong while recieving data! Disconnecting android...");
						try {
							soc.close();
						} catch (IOException e) {
							System.err.println("an IO derp");
						}
						return;
					} catch (SAXException e1) {
						System.err.println("Something went catostrophacally wrong while recieving data! Disconnecting android...");
						try {
							soc.close();
						} catch (IOException e) {
							System.err.println("an IO derp");
						}
						return;
					} catch (ParserConfigurationException e1) {
						System.err.println("Something went catostrophacally wrong while recieving data! Disconnecting android...");
						try {
							soc.close();
						} catch (IOException e) {
							System.err.println("an IO derp");
						}
						return;
					}
					


				}
				System.err.println("The socket was closed! Reciever");
			}
		}).start();
		//Server Sender
		(new Thread()
		{
			public void run()
			{
				while(!soc.isClosed()) // TODO Create sane operation here
				{
					// Send hit info to android
					//System.err.println(soc.isClosed());
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
						shooting = false;

						Element speedmodTag = doc.createElement("speedmod");
						rootElement.appendChild(speedmodTag);
						speedmodTag.appendChild(doc.createTextNode(""+speedFrac));

						TransformerFactory transformerFactory = TransformerFactory.newInstance();
						Transformer transformer = transformerFactory.newTransformer();
						DOMSource source = new DOMSource(doc);

						StreamResult result = new StreamResult(os);
						transformer.transform(source,result);
						os.write("\n".getBytes());
						os.flush();

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
					
					try {
						Thread.sleep(100);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}



				}
				System.err.println("The socket was closed! Sender");
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
	
	public void setLife(int l)
	{
		life = l;
		if(life<cachedLife)
		{
			(Message.obtain(ma.mainHandler, 1)).sendToTarget();
		}
		cachedLife = l;
	}
	
	public int getLife()
	{
		return life;
	}
	
	public boolean isAlive(){
		return (life>0);
	}





}
