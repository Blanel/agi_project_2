package com.example.agi_project_2_control;
import java.io.*;
import java.net.*;

public class Client {
	
	public void connect() throws UnknownHostException, IOException{
		Socket socket = new Socket("192.168.0.16", 15003);
		InputStream in = null;
		OutputStream out = null; 
		
		try
		{
			in = socket.getInputStream();
			out = socket.getOutputStream();
			
			out.write("Hello world!".getBytes("UTF-8"));
			out.flush();
		}
		finally
		{
			if (in != null)
				try
				{	in.close();
				}
				catch (Throwable ignore)
				{	//ignore
				}
			if (out != null)
				try
				{	out.close();
				}
				catch (Throwable ignore)
				{	//ignore
				}
		}
	}
}
