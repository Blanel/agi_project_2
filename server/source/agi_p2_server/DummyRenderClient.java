package agi_p2_server;

import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;
import java.util.Scanner;

public class DummyRenderClient {
	
	public static void main(String[] args)
	{
		try{
			Socket soc = new Socket("192.168.0.197",1234);
			InputStream is = soc.getInputStream();
			Scanner sc = new Scanner(is);
			while(true)
			{
				if(sc.hasNextLine())
				{
					System.out.println(sc.nextLine());
				}
				
			}
		}catch(IOException e)
		{
			
		}
		
	}

}
