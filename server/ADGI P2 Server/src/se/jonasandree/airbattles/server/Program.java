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
		try (ServerSocket server = new ServerSocket(15003, 20)) {
			final ArrayList<Client> clients = new ArrayList<>();
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
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}	
	}
}
