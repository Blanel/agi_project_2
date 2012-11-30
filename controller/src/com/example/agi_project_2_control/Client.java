package com.example.agi_project_2_control;
import java.io.*;
import java.net.*;
import java.util.Scanner;

public class Client {
	protected Socket socket = null;
	protected InputStream inputStream = null;
	protected OutputStream outputStream = null;
	protected Object sendMutex = new Object();
	public Scanner scanner;
	
	
	public void connect(String host, MainActivity main) throws UnknownHostException, IOException{
		this.socket = new Socket(host, 15003);
		//this.socket = new Socket("127.0.0.1", 55003);
		
		this.inputStream =  this.socket.getInputStream();
		this.outputStream = this.socket.getOutputStream();
		
		this.scanner = new Scanner(this.inputStream);
		main.onCreatAgain();
	}
	public void disconnect() {
			if (this.socket != null){
				try {
					this.socket.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			if (this.outputStream != null){
				try {
					this.outputStream.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			
			if (this.inputStream != null){
				try {
					this.inputStream.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
	}
	public void sendAction(String action) throws IOException{
		synchronized(this.sendMutex)
		{
			this.outputStream.write((action + "\n\n").getBytes("UTF-8"));
			this.outputStream.flush();
		}
	}
	
	public void reciveAction(Airplane airplane) throws IOException{
		for (String line; this.scanner.hasNextLine();){
			line = this.scanner.nextLine();
			if (line.length() == 0)
			{
				;
			}
			else if(line.equals("die")){
				airplane.hit();
			}	
		}
	}
}
