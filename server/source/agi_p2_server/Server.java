package agi_p2_server;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

public class Server implements Runnable{
	
	private ArrayList<AndroidClient> androids;
	private ArrayList<RenderClient> renderers;
	private GameState gs;
	private ServerSocket androidServsoc;
	private ServerSocket renderServsoc;
	
	
	
	public Server(int aport, int abacklog, int rport, int rbacklog)
	{
		androids = new ArrayList<AndroidClient>();
		renderers = new ArrayList<RenderClient>();
		
		gs = new GameState();
		new Thread(gs).start();
		
		try 
		{
			androidServsoc = new ServerSocket(aport,abacklog);
			renderServsoc = new ServerSocket(rport, rbacklog);
		} catch (IOException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
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
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}}).start();
		
		/*
		 * Renderer client connect listener
		 */
		(new Thread() {	public void run(){
				while(true)
				{
					try {
						Socket soc = renderServsoc.accept();
						renderers.add(new RenderClient(soc,gs));
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}}).start();
	}
	
	public static void main(String[] args)
	{
		
	}

	public void run() {
		// TODO Auto-generated method stub
		
	}

}
