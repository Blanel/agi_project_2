package agi_p2_server;
import java.util.ArrayList;

public class GameState {
	
	
	public ArrayList<Airplane> airplanes;
	public ArrayList<Bullet> bullets;
	
	private static final double planeHitbox = 0.5f;
	
	public GameState()
	{
		airplanes = new ArrayList<Airplane>();
		bullets = new ArrayList<Bullet>();
	}
	
	public void update()
	{
		// Get changes from all clients.
		
		// Apply all changes from all clients.
		
		// Move all bullets and planes
		moveEverything();
		
		// Calculate all collisions
		calculateCollisions();
		
		// Send data to renderclients
		
	}
	
	public void moveEverything()
	{
		for(int i = 0 ; i<airplanes.size() ; i++)
		{
			airplanes.get(i).move();
		}
		for(int i=0 ; i<bullets.size() ; i++)
		{
			bullets.get(i).move();
		}
	}
	
	
	
	public void calculateCollisions()
	{
		for(int i = 0 ; i<airplanes.size(); i++)
		{
			for(int j = 0 ; j<bullets.size() ; j++)
			{
				if(airplanes.get(i).getStatus()==-1)
					break;
				if(bullets.get(j).getStatus()>=0 && airplanes.get(i)!=bullets.get(j).getOwner() && airplanes.get(i).distance(bullets.get(j))<planeHitbox)
				{
					if(airplanes.get(i).hit())
					{
						bullets.get(j).getOwner().incrementKills();
						airplanes.get(i).setStatus(-1);
					}
					bullets.get(j).getOwner().incrementHits();
					bullets.get(j).setStatus(-1);
				}
			}
		}
	}
	
	
	
	

}
