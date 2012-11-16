package com.example.agi_project_2_control;
import java.io.*;
import java.net.*;

public class Client {
	
	public void connect() throws UnknownHostException, IOException{
		Socket socket = null;
		InputStream inputStream = null;
		OutputStream outputStream = null; 
		
		try {
			socket = new Socket("192.168.0.16", 15003);
			
			inputStream =  socket.getInputStream();
			outputStream = socket.getOutputStream();
			
			outputStream.write("Hello world!".getBytes("UTF-8"));
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		finally{
			if (socket != null){
				try {
					socket.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			if (outputStream != null){
				try {
					outputStream.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			
			if (inputStream != null){
				try {
					inputStream.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
	}
}
