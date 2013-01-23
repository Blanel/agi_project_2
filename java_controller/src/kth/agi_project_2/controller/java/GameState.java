package kth.agi_project_2.controller.java;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.StringReader;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Random;
import java.util.Vector;

import javax.swing.JPanel;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

public class GameState {
	
	private int playerId;
	private Vector<Vect> planes;
	private Vector<Vect> bullets;
	private BufferedReader br;
	private InputStream is;
	private InputStreamReader isr;
	
	private Socket soc;
	
	public GameState(int playerId, String host, int port)
	{
		this.playerId = playerId;
		planes = new Vector<Vect>();
		try {
			soc = new Socket(host, port);
			is = soc.getInputStream();
			isr = new InputStreamReader(is);
			br = new BufferedReader(isr);
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void updateState()
	{
		Coord playerPos = new Coord();
		Vector<Coord> enemyPos = new Vector<Coord>();
		Vector<Coord> bulletPos = new Vector<Coord>();
		
		// load all enemies and current player position into vector
		
		String line=null;
		try {
			if(br.ready())
			{
				line = br.readLine();
			}
		} catch (IOException e2) {
			System.err.println("IOException when reading line!");
		}

		// Is the line read sane?
		if(line!=null && line.startsWith("<?xml") && line.endsWith("</renderClient>") )
		{
			//System.err.println(line);
			// In that case, interrupt the timeout thread (as we have gotten a response) and parse the line.
			try {
				DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
				DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
				Document doc = docBuilder.parse(new InputSource(new StringReader(line)));
				Element planesElement = doc.getElementById("planes");
				
				NodeList planesNodes = planesElement.getChildNodes();
				
				for(int i = 0 ; i<planesNodes.getLength() ; i++)
				{
					//planesNodes.item(i).getFirstChild().getE
				}
				
			} catch ( IOException e) {
				System.err.println("Something went catostrophacally wrong while recieving data (IO)! Disconnecting android...");

			} catch (ParserConfigurationException | SAXException e) {
				System.err.println("Something went catostrophacally wrong while recieving data (Parser)! Disconnecting android...");

			}

		}
		else
		{
			if(line != null)
				System.err.println(line);
		}
		
		
		//Calculate the new positions:
		planes = new Vector<Vect>();
		for(int i= 0 ; i<enemyPos.size() ; i++)
		{
			planes.add(new Vect(playerPos.distance(enemyPos.get(i)), playerPos.getAngle(enemyPos.get(i))));
		}
		bullets = new Vector<Vect>();
		for(int i= 0 ; i<bulletPos.size() ; i++)
		{
			bullets.add(new Vect(playerPos.distance(bulletPos.get(i)), playerPos.getAngle(bulletPos.get(i))));
		}		
	}
	
	public void draw(JPanel contentPane)
	{
		
	}
	
	
	private class Vect
	{
		public double length;
		public double angle;
		
		public Vect()
		{
			length = 0;
			angle = 0;
		}
		
		public Vect(double l, double a)
		{
			length = l;
			angle = a;
		}
		
	}
	
	

}
