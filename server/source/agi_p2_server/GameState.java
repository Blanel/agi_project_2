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
		// TODO Get changes from all clients.
		
		// TODO Apply all changes from all clients. This includes updating rotations for planes, speeds for planes and spawning new bullets and/or planes.
		
		// Move all bullets and planes (Seems to work as expected)
		moveEverything();
		
		// Calculate all collisions (Seems to work as expected)
		calculateCollisions();
		
		// TODO Send data to renderclients
		
	}
	
	/**
	 * Moves all entities according to their properties.
	 * 
	 */
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
	

	
	
	/**
	 * Calculates collisions between shots and airplanes.
	 * Disregards collisions between airplanes.
	 * Disregards collisions between owned bullets.
	 * Disregards collisions between bullets that already have hit something or are queued for despawn
	 */
	public void calculateCollisions()
	{
		for(int i = 0 ; i<airplanes.size(); i++)
		{
			for(int j = 0 ; j<bullets.size() ; j++)
			{
				if(airplanes.get(i).getStatus()==-1)
					break;
				if(bullets.get(j).getStatus()>=0 && airplanes.get(i)!=bullets.get(j).getOwner() && airplanes.get(i).getPos().distance(bullets.get(j).getPos())<planeHitbox)
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
