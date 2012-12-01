package agi_p2_server;

import java.io.IOException;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.ArrayList;

public class Server {
	
	private ArrayList<AndroidClient> androids;
	public ArrayList<RenderClient> renderers;
	private GameState gs;
	private ServerSocket androidServsoc;
	private ServerSocket renderServsoc;
	
	private static final String serverMessage = "Usage: server <androidport> <renderport> <backlogConnections> \n\tandroidport: Integer for portnumber accepting connections from android\n\trendererport: Integer for portnumber accepting connections from renderer\n\tbacklogConnections: How many that can queue for connection to the server";
	
	public static void main(String[] args)
	{
		if(args.length!=3)
		{
			 System.out.println("No input given\n"+serverMessage+"\nDefault Settings applied");
			 new Server(1234, 20, 1233, 20);
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
	
	public Server(int aport, int abacklog, int rport, int rbacklog)
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
		System.out.println("Android Adress:"+ip+":"+androidServsoc.getLocalPort());
		System.out.println("Render Adress:"+ip+":"+renderServsoc.getLocalPort());
		androids = new ArrayList<AndroidClient>();
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
						AndroidClient temp = new AndroidClient(soc, gs);
						androids.add(temp);
						System.out.println("Android Client Connected: "+soc.getInetAddress().getHostAddress());
						(new Thread(temp)).start();
					} catch (IOException e) {
						System.err.println("Connection of android failed!");
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
						System.err.println("Connection of android failed!");
					}
				}
			}}).start();
		System.out.println("Render listener started");
		
		System.out.println("Server startup success!");
		
	}
		
	public void androidSync()
	{
		for(int i=0 ; i < androids.size() ; i++)
		{
			if(androids.get(i).isOpen())
				androids.get(i).update();
			else
			{
				System.out.println("Android Client Disconnected: "+androids.get(i).getSocket().getInetAddress());
				androids.remove(i--);
			}
		}
	}
	
	public void androidSend()
	{
		for(int i=0 ; i<androids.size() ; i++)
		{
			if(androids.get(i).isOpen())
				androids.get(i).sendEvents();
			else
			{
				System.out.println("Android Client Disconnected: "+androids.get(i).getSocket().getInetAddress());
				androids.remove(i--);
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
