package agi_p2_server;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.Random;

public class AndroidClient implements Runnable{
	
	private Airplane plane;
	private Socket soc;
	private boolean isShooting;
	private double rotation;
	private boolean isGearUp;
	private InputStream is;
	private OutputStream os;
	private GameState gs;
	private int cachedLife;
	
	
	public AndroidClient(Socket soc, GameState gs)
	{
		
		this.soc = soc;
		try {
			is = soc.getInputStream();
			os = soc.getOutputStream();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		isShooting = false;
		rotation = 0;
		double angle = new Random().nextDouble()*Math.PI*2;
		Coord centre = gs.getCentre();
		plane = new Airplane(gs.nextAId(),centre.x+Math.cos(angle+Math.PI), centre.y+Math.sin(angle+Math.PI),angle,this);
		gs.airplanes.add(plane);
		cachedLife = plane.getLife();
	}

	
	public void run() {
		while(!soc.isClosed())
		{
			
		}
	}
	public void update()
	{
		plane.addAngle(rotation);
		if(isGearUp)
		{
			plane.gearUp();
			isGearUp=false;
		}
		if(isShooting)
		{
			gs.bullets.add(new Bullet(gs.nextBId(), plane));
			isShooting=false;
		}

	}
	
	public void sendEvents()
	{
		if(plane.getLife()<cachedLife)
		{
			// TODO Send hit info to android
			
			if(plane.getLife()<=0)
			{
				try {
					soc.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
			
	}
	
	public boolean isOpen()
	{
		return soc.isClosed();
	}
	

}
