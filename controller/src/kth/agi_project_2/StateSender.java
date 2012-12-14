package kth.agi_project_2;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.StringReader;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketAddress;
import java.net.SocketTimeoutException;
import java.net.UnknownHostException;
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
	private MainActivity ma;

	private Socket soc =null;
	private OutputStream os = null;
	private InputStream is = null;
	private InputStreamReader isr = null;
	private BufferedReader br = null;
	private String host =null;
	private int port = 1234;

	private int cachedLife = 5;
	private int life = 5;

	private Thread timeoutThread; 
	private final long TIMEOUT = 15000;

	private Thread reconnectThread;
	//private boolean reconnecting = false;

	private Thread senderThread;
	private Thread listenerThread;

	private boolean running;

	private int id = -1;

	private final static long INTERVALL=40;

	private int connectMut;
	private int disconnMut;

	public StateSender(MainActivity m)
	{
		connectMut = 0;
		disconnMut = 1;
		running = true;
		ma = m;
		speedFrac = 0;
		shooting = false;
		screenHeight = 1;
		rotX = 0;
		rotY = 0;

		// A timeout thread. If nothing is heard from the server in a long while, disconnect 
		

		// A reconnect thread. If connection is lost, attempt to reconnect. 
		

		

		

	}

	// Connects with the specified host and port 
	public void connect() throws UnknownHostException, IOException, SocketTimeoutException
	{
		System.err.println("Connection called");
		if(disconnMut>connectMut)
		{
			connectMut++;
			System.err.println("Connection attempting");
			InetSocketAddress sa = new InetSocketAddress(host, port);
			soc = new Socket();
			//soc.setSoTimeout(1500);
			soc.connect(sa, 0);
			is = soc.getInputStream();
			os = soc.getOutputStream();
			isr = new InputStreamReader(is);
			br = new BufferedReader(isr);
			startListenerThreads();
			System.err.println("Connection established");
		}
	}

	public void disconnect(boolean error) throws IOException
	{
		System.err.println("Disconnection called");
		if(connectMut>=disconnMut)
		{
			disconnMut++;
			System.err.println("Disconnection attempted");
			br.close();
			isr.close();
			os.close();
			is.close();
			soc.close();
			if(!error)
			{
				running = false;
			}

			System.err.println("Disconnection done");
		}

	}

	private double getRotation()
	{
		return -((Math.atan2(rotX, rotY)+Math.PI/2)*10/Math.PI);
	}
	public void startListenerThreads()
	{
		if(listenerThread==null || !listenerThread.isAlive())
		{
			listenerThread = new Thread()
			{
				public void run()
				{
					while(!soc.isClosed() && running)
					{

						try {
							if(br.ready())
							{
								String line = br.readLine();
								timeoutThread.interrupt();
								DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
								DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
								Document doc = docBuilder.parse(new InputSource(new StringReader(line)));
								setLife(Integer.parseInt(doc.getElementsByTagName("life").item(0).getTextContent()));
								if(id==-1)
								{
									id = Integer.parseInt(doc.getElementsByTagName("id").item(0).getTextContent());
								}
							}
						} catch (IOException e1) {
							System.err.println("Something went catostrophacally wrong while recieving data! Disconnecting android...");
							try {
								disconnect(true);
							} catch (IOException e) {
								System.err.println("an IO derp");
							}
							return;
						} catch (SAXException e1) {
							System.err.println("Something went catostrophacally wrong while recieving data! Disconnecting android...");
							try {
								disconnect(true);
							} catch (IOException e) {
								System.err.println("an IO derp");
							}
							return;
						} catch (ParserConfigurationException e1) {
							System.err.println("Something went catostrophacally wrong while recieving data! Disconnecting android...");
							try {
								disconnect(true);
							} catch (IOException e) {
								System.err.println("an IO derp");
							}
							return;
						}
					}
					System.err.println("The socket was closed! Reciever");
				}
			};
			listenerThread.start();
		}
		if(senderThread==null || !senderThread.isAlive()){
			senderThread = new Thread()
			{
				public void run()
				{
					while(!soc.isClosed() && running) // TODO Create sane operation here
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

							Element idTag = doc.createElement("id");
							rootElement.appendChild(idTag);
							idTag.appendChild(doc.createTextNode(""+id));

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
							//System.err.println("Sent: "+System.currentTimeMillis());

						} catch (ParserConfigurationException e1) {
							System.err.println("Something went catostrophacally wrong while sending data! Disconnecting android...");
							try {
								disconnect(true);
							} catch (IOException e) {
								System.err.println("an IO derp");
							}
							return;
						} catch (TransformerException e1) {
							System.err.println("Something went catostrophacally wrong while sending data! Disconnecting android...");
							try {
								disconnect(true);
							} catch (IOException e) {
								System.err.println("an IO derp");
							}
						} catch (IOException e1) {
							System.err.println("Something went catostrophacally wrong while sending data! Disconnecting android...");
							try {
								disconnect(true);
							} catch (IOException e) {
								System.err.println("an IO derp");
							}
						}

						try {
							Thread.sleep(120);
						} catch (InterruptedException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}



					}
					System.err.println("The socket was closed! Sender");
				}
			};
			senderThread.start();
		}
		if(timeoutThread==null || !timeoutThread.isAlive())
		{
			timeoutThread = new Thread()
			{
				public void run()
				{

					while(running)
					{

						try {
							sleep(TIMEOUT);
							if(soc != null && !soc.isClosed() && connectMut==disconnMut)
							{

								//shutDown();
								System.err.println("Server timed out!");

								try{
									disconnect(true);
								}
								catch(IOException e)
								{
									System.err.println("IO Exception!");
								}
							}
						} catch (InterruptedException e) {
							// Do nothing!
						}
					}
					System.err.println("TimeoutThread has reached its end");
				}
			};
			timeoutThread.start();
		}
		if(reconnectThread==null || !reconnectThread.isAlive())
		{
			reconnectThread = new Thread()
			{
				public void run()
				{
					while(running)
					{
						try{
							sleep(1000);
							if(soc !=null && soc.isClosed())
							{
								sleep(130);
								System.err.println("Reconnect Attempted");
								try {
									connect();
								} catch (UnknownHostException e) {
									System.err.println("Reconnect Failed. Shitty Host");
									try {
										disconnect(true);
									} catch (IOException e1) {
										// TODO Auto-generated catch block
										e1.printStackTrace();
									}
								} catch (IOException e) {
									System.err.println("Reconnect Failed. General IO error");
									try {
										disconnect(true);
									} catch (IOException e1) {
										// TODO Auto-generated catch block
										e1.printStackTrace();
									}
								}
							}

						}
						catch(InterruptedException e)
						{

						}

					}
					System.err.println("Reconnect Thread has reached its end");
				}

			};
			reconnectThread.start();
		}

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

	public void setHost(String host, int port)
	{
		this.host = host;
		this.port = port;
	}





}
