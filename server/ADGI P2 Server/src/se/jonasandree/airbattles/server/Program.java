package se.jonasandree.airbattles.server;
//ipconfig

import java.io.*;
import java.net.*;
import java.util.ArrayList;

public class Program {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try (ServerSocket server = new ServerSocket(15003, 20)) {
			final ArrayList<Client> clients = new ArrayList<>();
			for(;;){
				final Socket socket = server.accept();
				Thread thread = new Thread("Client-" + socket.getRemoteSocketAddress())
						{
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
										clients.add(client);
									}
									client.start();
								} catch (IOException e) {
									// TODO Auto-generated catch block
									e.printStackTrace();
								}
							}
						};
				thread.setDaemon(true); // N�r alla ickedemoner har avslutat s� st�ngs programmet av.
				thread.start();
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
