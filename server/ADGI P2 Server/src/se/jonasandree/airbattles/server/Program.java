package se.jonasandree.airbattles.server;
//ipconfig

import java.io.*;
import java.net.*;
import java.util.ArrayList;
import java.util.Scanner;

public class Program implements Runnable {
	private static OutputStream[] clientOuts = new OutputStream[1024];
	private static String action = "die";
	final ArrayList<Client> renderingClients = new ArrayList<>();
	final ArrayList<Client> androidClients = new ArrayList<>();
	
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
				Thread threadClientWrite = new Thread(){
					@Override
					public void run(){
						while(true){							
							try {
								Thread.sleep(17);
							} catch (InterruptedException e) {
								e.printStackTrace();
							}
							for (Client client : clients){
								if (client.getClientType() == false && client.isAClient == true){
									renderingClients.add(client);
									//System.out.println("AndroidClient: "+client.getClientType()+"");
								}
								else if (client.isAClient == true){
									//System.out.println("AndroidClient: "+client.getClientType()+"");
									try {
										String alivetemp = "no";
										if (client.airplane.getAlive()){
											alivetemp = "yes";
										}
										else {
											alivetemp = "no";
										}
										//System.out.println("Amount of rendering clients: "+ renderingClients.size());
										for (Client client1 :renderingClients){
											System.out.println("aireplane: " + client.getIndex()+"\n"+"alive: " + alivetemp+"\n");
											client1.write(("aireplane: " + client.getIndex()+"\n" + "alive: "+alivetemp+"\n").getBytes("UTF-8"));
											if (client.android){
												if(client.airplane.getAlive()){
													System.out.println("x: "+client.airplane.getPositionX()+"\n"+"y: "+client.airplane.getPositionY()+"\n"+"rotation: "+client.airplane.getRotation()+"\n");
													
													client1.write(("x: "+client.airplane.getPositionX()+"\n"+"y: "+client.airplane.getPositionY()+"\n"+"rotation: "+client.airplane.getRotation()+"\n").getBytes("UTF-8"));	
												}
											}
										}
									} catch (UnsupportedEncodingException e) {
										;
									}
										ArrayList<Bullet> bullets = client.airplane.getBullets();
										if (bullets.isEmpty()){
											;
										}
										else{
											for (int bindex = 0; bindex < bullets.size(); bindex++){
												//System.out.println(bullets.size()+ ": 2\n");
												bullets.get(bindex).uppdatePosition();
												String bexists = "no";
												if(bullets.get(bindex).getExist()){
													bexists = "yes";
												}
												
												System.out.println("bullet: "+ bindex + "\n"+ "x: "+ bullets.get(bindex).getPositionX()+"\n"+ "y: "+ bullets.get(bindex).getPositionY()+"\n"+ "rotation: "+ bullets.get(bindex).getRotation()+"\n" + "exists: "+bexists);
												if (bullets.get(bindex).getExist()){
													for (Client client1 :renderingClients){
														try {
															System.out.println(("bullet: "+ bindex + "\n"+ "x: "+ bullets.get(bindex).getPositionX()+"\n"+ "y: "+ bullets.get(bindex).getPositionY()+"\n"+ "rotation: "+ bullets.get(bindex).getRotation()+"\n" + "exists: "+bexists));
															
															client1.write(("bullet: "+ bindex + "\n"+ "x: "+ bullets.get(bindex).getPositionX()+"\n"+ "y: "+ bullets.get(bindex).getPositionY()+"\n"+ "rotation: "+ bullets.get(bindex).getRotation()+"\n" + "exists: "+bexists).getBytes("UTF-8"));
														}catch (UnsupportedEncodingException e) {
															;
														}
													}
												}
												if (bullets.get(bindex).getExist() == false){
													System.out.println("Bullet Removed:");
													client.airplane.removeBullet(bindex);
												}
											}
										}
									}
							}
						}
					}
				};
				thread.setDaemon(true);
				thread.start();
				threadClientWrite.setDaemon(true);
				threadClientWrite.start();
			}
		}catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
