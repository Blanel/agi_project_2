package se.jonasandree.airbattles.server;
//ipconfig

import java.io.*;
import java.net.*;
import java.util.ArrayList;
import java.util.Scanner;

public class Program implements Runnable {
	private static OutputStream[] clientOuts = new OutputStream[1024];
	private static String action = "die"; 
	
	/**
	 * @param args
	 */
	public static void main(String[] args) throws UnsupportedEncodingException {
		Thread thread = new Thread(new Program());
		thread.setDaemon(true);
		thread.start();
		
		Scanner stdin = new Scanner(System.in);
		while(stdin.hasNextLine()){
			if(stdin.nextLine().equals(action)){
				try {
					clientOuts[0].write((action+"\n\n").getBytes("UTF-8"));
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				System.out.print("die was sent to client 0");
			}
		}
	}
	@Override
	public void run(){
		final ArrayList<Client> clients = new ArrayList<>();
		try (ServerSocket server = new ServerSocket(15003, 20)) {
			for(;;){
				final Socket socket = server.accept();
				Thread thread = new Thread("Client-" + socket.getRemoteSocketAddress()){
					/**
					 * logik f�r tr�den(non-Javadoc)
					 * @see java.lang.Thread#run()
					 */
					@Override
					public void run(){
						try (final InputStream in 	= socket.getInputStream()
							;final OutputStream out = socket.getOutputStream())
						{
							Client client;
							synchronized (clients)
							{
								int index = clients.size();
								client = new Client(index, in, out);
								Program.clientOuts[index] = out;
								clients.add(client);
							}
							client.start();
						} catch (IOException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
					}
				};		
				thread.setDaemon(true);
				thread.start();
			}
		}catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		Thread threadClientWrite = new Thread(){
			@Override
			public void run(){
				while(true){
					try {
						Thread.sleep(100);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					
					for (Client client : clients){
						if (client.getClientType()){
							
						}
						else{
							try {
								client.write(("a" + client.airplane.getIndex()+"a"+(client.airplane.getAlive()+"\n\n")).getBytes("UTF-8"));
								if(client.airplane.getAlive()){
									client.write(("a" + client.airplane.getIndex()+"x"+client.airplane.getPositionX()+"\n\n").getBytes("UTF-8"));
									client.write(("a" + client.airplane.getIndex()+"y"+client.airplane.getPositionY()+"\n\n").getBytes("UTF-8"));
									client.write(("a" + client.airplane.getIndex()+"r"+client.airplane.getRotation()+"\n\n").getBytes("UTF-8"));	
								}
							} catch (UnsupportedEncodingException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
						}
						for(int i = 0; i < client.airplane.bullets.length; i++){				
							try {
								client.write(("b" + client.airplane.getIndex()+ "bi"+ i + "e" + client.airplane.getBullets(i).getExist()).getBytes("UTF-8"));
								if(client.airplane.getBullets(i).getExist()){
									client.write(("b" + client.airplane.getIndex()+ "bi"+ i + "x" + client.airplane.getBullets(i).getPositionX()+"\n\n").getBytes("UTF-8"));
									client.write(("b" + client.airplane.getIndex()+ "bi"+ i + "y" + client.airplane.getBullets(i).getPositionY()+"\n\n").getBytes("UTF-8"));	
								} 	
							}catch (UnsupportedEncodingException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
							client.airplane.getBullets(i).uppdatePosition();
						}
						//client.airplane.uppdateGas();
					}
				}
			}
		};
		threadClientWrite.setDaemon(true);
		threadClientWrite.start();
	}
}
