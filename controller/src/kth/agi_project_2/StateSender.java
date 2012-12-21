package kth.agi_project_2;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.StringReader;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.net.UnknownHostException;

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


	// Airplane variables
	private double speedFrac;
	private boolean shooting;
	private int cachedLife = 5;
	private int life = 5;
	private int id = -1;



	// Connection Variables
	private Socket soc =null;
	private OutputStream os = null;
	private InputStream is = null;
	private InputStreamReader isr = null;
	private BufferedReader br = null;
	private String host =null;
	private int port = 1234;
	private int connectMut;
	private int disconnMut;

	// Hardware Variables
	private int screenHeight;
	private float rotX;
	private float rotY;

	// App Variables
	private MainActivity ma;
	private boolean running;

	// Threading
	private Thread timeoutThread; 
	private Thread reconnectThread;
	private Thread senderThread;
	private Thread listenerThread;
	private final static long RECONNECT_WAIT = 3000;
	private final static long RECONNECT_RETRIES = -1;
	private final static long TIMEOUT = 15000;
	private final static long SENDER_WAIT = 120;
	private final static long LISTENER_WAIT = 10;



	public StateSender(MainActivity m)
	{
		ma = m;

		cachedLife = 5;
		life = 5;
		id = -1;

		soc =null;
		os = null;
		is = null;
		isr = null;
		br = null;
		host =null;
		port = 1234;
		connectMut = 0;
		disconnMut = 1;

		running = true;

		speedFrac = 0;
		shooting = false;
		screenHeight = -1;
		rotX = 0;
		rotY = 0;
	}

	public void setHost(String host, int port)
	{
		this.host = host;
		this.port = port;
	}

	public boolean connect() 
	{
		System.err.println("Connection called");
		if(disconnMut>connectMut)
		{
			try{


				connectMut++;

				System.err.println("Connection attempting");

				InetSocketAddress sa = new InetSocketAddress(host, port);
				soc = new Socket();
				soc.connect(sa, 0);
				is = soc.getInputStream();
				os = soc.getOutputStream();
				isr = new InputStreamReader(is);
				br = new BufferedReader(isr);

				startListenerThreads();

				System.err.println("Connection established");
				return true;
			}
			catch(IOException e)
			{
				System.err.println("Something went wrong connecting. IOException.");
				return false;
			}
		}
		return false;
	}

	public boolean disconnect(boolean error)
	{
		System.err.println("Disconnection called");
		if(connectMut>=disconnMut)
		{
			try
			{
				disconnMut++;

				System.err.println("Disconnection attempted");

				br.close();
				isr.close();
				os.close();
				is.close();
				soc.close();
			}
			catch(IOException e)
			{
				System.err.println("Disconnect failed");
				return false;
			}

			if(!error)
			{
				running = false;
			}

			System.err.println("Disconnection done");
			return true;
		}
		return false;

	}

	/**
	 * Initializes and starts threads if threads are not alive. 
	 */
	public void startListenerThreads()
	{
		// The listener thread listens for stuff sent from the server to the android
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
							else
							{
								try {
									sleep(LISTENER_WAIT);
								} catch (InterruptedException e) {
									// Do nothing
								}
							}
						} 
						// Lots of errorhandling!
						catch (IOException e1) {
							System.err.println("Something went catostrophacally wrong while recieving data! Disconnecting android...");
								disconnect(true);
						} catch (SAXException e1) {
							System.err.println("Something went catostrophacally wrong while recieving data! Disconnecting android...");
								disconnect(true);

							return;
						} catch (ParserConfigurationException e1) {
							System.err.println("Something went catostrophacally wrong while recieving data! Disconnecting android...");

								disconnect(true);
							return;
						}
					}
					System.err.println("The socket was closed! Reciever");
				}
			};
			listenerThread.start();
		}

		// The sender thread sends data to the server
		if(senderThread==null || !senderThread.isAlive()){
			senderThread = new Thread()
			{
				public void run()
				{
					while(!soc.isClosed() && running)
					{
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

						}
						// Lots of errorhandling!
						catch (ParserConfigurationException e1) {
							System.err.println("Something went catostrophacally wrong while sending data! Disconnecting android...");
								disconnect(true);
							return;
						} catch (TransformerException e1) {
							System.err.println("Something went catostrophacally wrong while sending data! Disconnecting android...");
								disconnect(true);
							return;
						} catch (IOException e1) {
							System.err.println("Something went catostrophacally wrong while sending data! Disconnecting android...");
								disconnect(true);
							return;
						}

						try {
							Thread.sleep(SENDER_WAIT);
						} catch (InterruptedException e) {
							// Do nothing
						}
					}
					System.err.println("The socket was closed! Sender");
				}
			};
			senderThread.start();
		}

		// The timeout thread checks if the server has taken an abnormally long time to respond.
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
								System.err.println("Server timed out!");
									disconnect(true);
							}
						} catch (InterruptedException e) {
							// Do nothing
						}
					}
					System.err.println("TimeoutThread has reached its end");
				}
			};
			timeoutThread.start();
		}

		// The reconnect thread attempts to reconnect a connection that has been severed for any reason.
		if(reconnectThread==null || !reconnectThread.isAlive())
		{
			reconnectThread = new Thread()
			{
				public void run()
				{
					int retries = 0;
					while(running && (retries < RECONNECT_RETRIES || RECONNECT_RETRIES == -1))
					{
						try{
							sleep(RECONNECT_WAIT);
							if(soc !=null && soc.isClosed())
							{
								sleep(130);
								System.err.println("Reconnect Attempted");
								retries++;
								if(connect())
								{
									System.err.println("Reconnect Success");
									retries=0;
								}
								else
								{
									System.err.println("Reconnect failed");
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

	public int getScreenHeight() {
		return screenHeight;
	}

	public void setScreenHeight(int screenHeight) {
		this.screenHeight = screenHeight;
	}

	public double getSpeedFrac() {
		return speedFrac;
	}

	public void setSpeedFrac(double speedFrac) {
		this.speedFrac = speedFrac;
	}

	private double getRotation()
	{
		return ((Math.atan2(rotX, rotY)+Math.PI/2)*10/Math.PI);
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
			(Message.obtain(ma.mainHandler, 1)).sendToTarget();
		cachedLife = l;
		
		if(life == 0)
		{
			disconnect(false);
		}
	}

	public int getLife()
	{
		return life;
	}

	public boolean isAlive(){
		return (life>0);
	}
}
