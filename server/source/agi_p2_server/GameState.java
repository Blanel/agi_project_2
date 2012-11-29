package agi_p2_server;
import java.util.ArrayList;

public class GameState {
	
	
	public ArrayList<Airplane> airplanes;
	public ArrayList<Bullet> bullets;
	private int planeIdPool;
	private int bulletIdPool;
	private final double MAX_DISTANCE = 128;
	
	private static final double planeHitbox = 0.5f;
	
	public GameState()
	{
		airplanes = new ArrayList<Airplane>();
		bullets = new ArrayList<Bullet>();
		planeIdPool = 0;
		bulletIdPool = 0;
	}
	
	/**
	 * Updates gamestate
	 */
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
		// Move all planes
		for(int i = 0 ; i<airplanes.size() ; i++)
		{
			airplanes.get(i).move();
		}
		// Move all bullets
		for(int i=0 ; i<bullets.size() ; i++)
		{
			bullets.get(i).move();
		}
		//Find centre of all planes and turn any planes that are too far away into the centre again
		Coord centre = getCentre();
		for(int i=0 ; i<airplanes.size() ; i++)
		{
			if(airplanes.get(i).getPos().distance(centre)>=MAX_DISTANCE)
			{
				airplanes.get(i).setAngle(airplanes.get(i).getPos().getAngle(centre));
			}
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
				// If plane is already dead, skip consequent calculations on plane
				if(airplanes.get(i).getStatus()==-1) 
					break;
				// For every bullet that is still alive and not owned by the current plane, check for collision.
				if(bullets.get(j).getStatus()>=0 && airplanes.get(i)!=bullets.get(j).getOwner() && airplanes.get(i).getPos().distance(bullets.get(j).getPos())<planeHitbox)
				{
					if(airplanes.get(i).hit()) // Register a hit, if true plane has been killed.
					{
						bullets.get(j).getOwner().incrementKills();
					}
					bullets.get(j).getOwner().incrementHits();
					bullets.get(j).setStatus(-1); // Set status of bullet as a hit. (Not alive anymore)
				}
			}
		}
	}
	
	/**
	 * Gets centre of all airplanes.
	 * @return Coordinates for centre
	 */
	private Coord getCentre()
	{
		Coord temp = new Coord();
		for(int i=0 ; i<airplanes.size(); i++)
		{
			temp.x += airplanes.get(i).getPos().x;
			temp.y += airplanes.get(i).getPos().y;
		}
		temp.x /= airplanes.size();
		temp.y /= airplanes.size();
		return temp;
	}
	
	
	

}
