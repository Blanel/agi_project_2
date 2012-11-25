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
	
	public Airplane airplane;
	
	public int screenWidth;
	public int screenHeight;
	
	public final int index;
	public final InputStream in;
	public final OutputStream out;
	public final Scanner scanner;
	public boolean android = false;
	public boolean renderingClient = false;
	public int bIndex = 0;
	
	public void start() throws IOException{
		for (String line; this.scanner.hasNextLine();){
			line = this.scanner.nextLine();
			if (line.isEmpty()){
				System.out.print("");
				System.out.flush();
			}
			else{
				if (!this.android && !renderingClient){
					if (line.substring(0, 7).equals("Android")){
						this.airplane = new Airplane(index);
						this.android = true;
					}
					else if (line.substring(0, 15).equals("renderingClient")){
						this.renderingClient = true;
					}
				}
				else if(this.android){
					if(line.substring(0, 1).equals("x")){
						this.airplane.setRotationX(Float.valueOf(line.substring(1)));

						this.airplane.uppdateGas();
						this.airplane.uppdateSpeed();
						//System.out.println(line);
					}
					else if(line.substring(0, 1).equals("y")){
						this.airplane.setRotationY(Float.valueOf(line.substring(1)));
						
						System.out.println("velocity" + this.airplane.getVelocity());
						System.out.println("speed" + this.airplane.getSpeed());
						System.out.println("rotation "+ this.airplane.getRotation());
						System.out.println("x "+ this.airplane.getPositionX());
						System.out.println("y "+ this.airplane.getPositionY()+ "\n");
					}
					else if (line.substring(0, 1).equals("f")){
						this.airplane.addBullets(this.bIndex);
						this.bIndex = this.bIndex+1;
						System.out.print("\n" + line + " index "+ this.index);
					}
					else if (line.substring(1, 2).equals("g")){
						if (line.substring(0, 1).equals("+")){
							float massage = 1-Float.valueOf(line.substring(4))/this.screenHeight;
							this.airplane.setSpeed(massage);
						}
						if (line.substring(0, 1).equals("-")){
							this.airplane.setSpeed(0);
							this.airplane.noGas();
							//System.out.print("\n" + line + " index "+ this.index);
						}
					}
					else if (line.substring(0, 6).equals("screen")){
						System.out.println(line);
						if(line.substring(6, 7).equals("W")){
							screenWidth = Integer.valueOf(line.substring(11));
						}
						if(line.substring(6, 7).equals("H")){
							screenHeight = Integer.valueOf(line.substring(12));
						}
					}
					else{
						System.out.print("\n Not rekogniceble " + line + " index "+ this.index);
						System.out.flush();
					}
				}
				
			}
		}
	}
	public boolean getClientType(){
		if (this.android){
			return true;
		}
		else{
			return false;
		}
	}
	public void write(byte[] bytes) {
		try {
			this.out.write(bytes);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
