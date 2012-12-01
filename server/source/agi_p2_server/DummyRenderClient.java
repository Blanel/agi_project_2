package agi_p2_server;

import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;
import java.util.Scanner;

public class DummyRenderClient {
	
	public static void main(String[] args)
	{
		try{
			Socket soc = new Socket(args[0],Integer.parseInt(args[1]));
			InputStream is = soc.getInputStream();
			Scanner sc = new Scanner(is);
			while(!soc.isClosed())
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
