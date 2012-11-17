package se.jonasandree.airbattles.server;

import java.io.*;
import java.util.Scanner;


public class Client {
	public Client(int index, InputStream in, OutputStream out)
	{
		this.index = index;
		this.in = in;
		this.out = out;
		this.scanner = new Scanner(this.in);
	}
	
	public final int index;
	public final InputStream in;
	public final OutputStream out;
	public final Scanner scanner;
	
	public void start() throws IOException
	{
		for (String line; this.scanner.hasNextLine();)
		{
			line = this.scanner.nextLine();
			if (line.isEmpty())
			{
				System.out.print(".");
				System.out.flush();
			}
			else
				System.out.print("\n" + line + " :was sent from client number [" + this.index + "]");
		}
	}
}
