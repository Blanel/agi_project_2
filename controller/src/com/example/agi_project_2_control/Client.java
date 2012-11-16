package com.example.agi_project_2_control;
import java.io.*;
import java.net.*;

public class Client {
	
	public void connect() throws UnknownHostException, IOException{
		Socket nsocket = new Socket("192.168.0.16", 15003);
		InputStream nin = null;
		OutputStream nout = null; 
		
		try
		{
			nin = nsocket.getInputStream();
			nout = nsocket.getOutputStream();
			
			nout.write("Hello world!".getBytes("UTF-8"));
			nout.flush();
		}
		finally
		{
			if (in != null)
				try
				{	nin.close();
				}
				catch (Throwable ignore)
				{	//ignore
				}
			if (nout != null)
				try
				{	nout.close();
				}
				catch (Throwable ignore)
				{	//ignore
				}
		}
	}
}
