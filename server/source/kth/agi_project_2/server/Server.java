/**
 * Server loop. Starts and runs the server, listening for connections.
 */
package kth.agi_project_2.server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.ArrayList;

public class Server {

	private ArrayList<ControllerClient> controllers;
	public ArrayList<RenderClient> renderers;
	private GameState gs;
	private ServerSocket androidServsoc;
	private ServerSocket renderServsoc;

	private static final String serverMessage = "Usage: server <controllerport> <renderport> <backlogConnections> \n\tcontrollerport: Integer for portnumber accepting connections from controllers\n\trendererport: Integer for portnumber accepting connections from renderer\n\tbacklogConnections: How many that can queue for connection to the server";

	public static void main(String[] args) throws IOException 
	{
		if(args.length!=3)
		{
			System.out.println("No input given\n"+serverMessage+"\nDefault Settings applied");
			new Server(1234, 20, 1235, 20);
		}
		else
		{
			try{
				new Server(Integer.parseInt(args[0]), Integer.parseInt(args[2]), Integer.parseInt(args[1]), Integer.parseInt(args[2]));
			}
			catch(NumberFormatException e)
			{
				System.out.println("Invalid input\n"+serverMessage+"\n\nServer Stoped");
			}
		}
	}

	public Server(int aport, int abacklog, int rport, int rbacklog) throws IOException
	{
		System.out.println("Server started...");
		try 
		{
			androidServsoc = new ServerSocket(aport,abacklog);
			renderServsoc = new ServerSocket(rport, rbacklog);
		} catch (IOException e) 
		{
			System.err.println("Can't bind serverports! Try other ports");
			return;
		}
		String ip="UNKNOWN";
		try {
			ip = InetAddress.getLocalHost().getHostAddress();
		} catch (UnknownHostException e) {
			System.err.println("Unable to find local ip. Continuing without, but may be unpredictable.");
		}
		System.out.println("Controller Adress:"+ip+":"+androidServsoc.getLocalPort());
		System.out.println("Render Adress:"+ip+":"+renderServsoc.getLocalPort());
		controllers = new ArrayList<ControllerClient>();
		renderers = new ArrayList<RenderClient>();

		gs = new GameState(this);
		new Thread(gs).start();



		/*
		 * Android client connect listener
		 */
		(new Thread() {	public void run(){
			while(true)
			{
				try {
					Socket soc = androidServsoc.accept();
					ControllerClient temp = new ControllerClient(soc, gs);
					controllers.add(temp);
					System.out.println("Controller Client Connected: "+soc.getInetAddress().getHostAddress());
					(new Thread(temp)).start();
				} catch (IOException e) {
					System.err.println("Connection of Controller failed!");
				}
			}
		}}).start();
		System.out.println("Android listener started");

		/*
		 * Renderer client connect listener
		 */
		(new Thread() {	public void run(){
			while(true)
			{
				try {
					Socket soc = renderServsoc.accept();
					renderers.add(new RenderClient(soc,gs));
					System.out.println("Render Client Connected: "+soc.getInetAddress().getHostAddress());
				} catch (IOException e) {
					System.err.println("Connection of Render Client failed!");
				}
			}
		}}).start();
		System.out.println("Render listener started");
		System.out.println("Server startup success!");

		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader br = new BufferedReader(isr);
		while(true) //TODO Fix lazy coding
		{
			String command = br.readLine();
			String[] tokens = command.split(" ");

			if(tokens.length == 1)
			{
				if(tokens[0].matches("lv"))
				{
					System.out.println("Hitbox: "+gs.planeHitbox);
					System.out.println("Distance: "+gs.maxDistance);
					System.out.println("Frequency: "+gs.updateFrequency);
					System.out.println("PBS: "+gs.planeBaseSpeed);
					System.out.println("PMS: "+gs.planeModSpeed);
					System.out.println("BBS: "+gs.bulletBaseSpeed);
					System.out.println("PBL: "+gs.planeBaseLife);
					System.out.println("BTTL: "+gs.bulletTtl);
				}
				else
				{
					System.err.println("Shitty input");
				}
			}
			else if(tokens.length==2)
			{
				if(tokens[0].matches("ttl"))
				{
					gs.bulletTtl = Integer.parseInt(tokens[1]);
				}
				else if(tokens[0].matches("hb"))
				{
					gs.planeHitbox = Double.parseDouble(tokens[1]);
				}
				else if(tokens[0].matches("d"))
				{
					gs.maxDistance = Double.parseDouble(tokens[1]);
				}
				else if(tokens[0].matches("f"))
				{
					gs.updateFrequency = Long.parseLong(tokens[1]);
				}
				else if(tokens[0].matches("pbs"))
				{
					gs.planeBaseSpeed = Double.parseDouble(tokens[1]);
				}
				else if(tokens[0].matches("pms"))
				{
					gs.planeModSpeed = Double.parseDouble(tokens[1]);
				}
				else if(tokens[0].matches("bbs"))
				{
					gs.bulletBaseSpeed = Double.parseDouble(tokens[1]);
				}
				else if(tokens[0].matches("pbl"))
				{
					gs.planeBaseLife = Integer.parseInt(tokens[1]);
				}
				else
				{
					System.err.println("Shitty input");
				}
			}
			else
			{
				System.err.println("Shitty input");
			}
		}

	}

	public void androidSync()
	{
		for(int i=0 ; i < controllers.size() ; i++)
		{
			if(controllers.get(i).isOpen())
				controllers.get(i).update();
			else
			{
				System.out.println("Controller Client Disconnected: "+controllers.get(i).getSocket().getInetAddress());
				controllers.remove(i--);
			}
		}
	}

	public void androidSend()
	{
		for(int i=0 ; i<controllers.size() ; i++)
		{
			if(controllers.get(i).isOpen())
				controllers.get(i).sendEvents(false);
			else
			{
				System.out.println("Controller Client Disconnected: "+controllers.get(i).getSocket().getInetAddress());
				controllers.remove(i--);
			}
		}
	}

	public void rendererSend()
	{
		for(int i=0 ; i<renderers.size(); i++)
		{
			if(renderers.get(i).isOpen())
				renderers.get(i).send();
			else
			{
				System.out.println("Render Client Disconnected: "+renderers.get(i).getSocket().getInetAddress());
				renderers.remove(i--);
			}
		}
	}
}
