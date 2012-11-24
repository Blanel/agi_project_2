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
		for (String line; this.scanner.hasNextLine();){
			line = this.scanner.nextLine();
			if (line.isEmpty()){
				System.out.print(".");
				System.out.flush();
			}
			else{				
				if (line.substring(0, 7).equals("Android")){
					System.out.print("\n" + line + " index "+ this.index);
				}
				else if (line.substring(0, 6).equals("screen")){
					if(line.substring(6, 7).equals("W")){
						System.out.print("\n" + line.substring(11) + " index "+ this.index);
					}
					if(line.substring(6, 7).equals("H")){
						System.out.print("\n" + line.substring(12) + " index "+ this.index);
					}
				}
				else if(line.substring(0, 1).equals("x")){
					System.out.print("\n" + line.substring(1) + " index "+ this.index);
				}
				else if(line.substring(0,1).equals("y")){
					System.out.print("\n" + line.substring(1) + " index "+ this.index);
				}
				else if (line.substring(0, 4).equals("fire")){
					System.out.print("\n" + line + " index "+ this.index);
				}
				else if (line.substring(0, 4).equals("+gas")){
					System.out.print("\n" + line + " index "+ this.index);
				}
				else if (line.substring(0, 4).equals("-gas")){
					System.out.print("\n" + line + " index "+ this.index);
				}
				else{
					System.out.print("\n Not rekogniceble " + line + " index "+ this.index);
				}
			}
		}
	}
}
