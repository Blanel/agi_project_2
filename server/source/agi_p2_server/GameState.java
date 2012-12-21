package agi_p2_server;
import java.util.LinkedList;
import java.util.ListIterator;

public class GameState implements Runnable {


	public LinkedList<Airplane> airplanes;
	private ListIterator<Airplane> aIt;
	public LinkedList<Bullet> bullets;
	private ListIterator<Bullet> bIt;
	private int planeIdPool;
	private int bulletIdPool;

	private Server srv;

	public double planeHitbox;
	public double maxDistance;
	public long updateFrequency;
	public double planeBaseSpeed;
	public double planeModSpeed;
	public double bulletBaseSpeed;
	public int planeBaseLife;
	public int bulletTtl;


	public GameState(Server srv)
	{
		this.srv = srv;
		airplanes = new LinkedList<Airplane>();
		bullets = new LinkedList<Bullet>();
		planeIdPool = 0;
		bulletIdPool = 0;
		
		planeHitbox = 0.5f;
		maxDistance = 48;
		updateFrequency = 4000000;
		planeBaseSpeed = 0.05;
		planeModSpeed = 0.1;
		bulletBaseSpeed = 0.2;
		planeBaseLife = 5;
		bulletTtl = 180;
	}

	/**
	 * Updates gamestate
	 */
	public void run()
	{
		System.out.println("Gamestate loop started");
		long start = System.nanoTime();
		long end = 0;
		while(true)
		{
			// Get changes from all clients.
			srv.androidSync();
			
			// Move all bullets and planes (Seems to work as expected)
			moveEverything();
	
			// Calculate all collisions (Seems to work as expected)
			calculateCollisions();
	
			// Keeps an eye on the time a loop takes to run
			end = System.nanoTime();
			if(end-start < updateFrequency)
			{
				while(end-start < updateFrequency)
				{
					end = System.nanoTime();
				}
			}
			else if((end-start)-updateFrequency>1000000000)
			{
				System.err.println("Server can't keep up! "+((Math.floor((float)(end-start)-updateFrequency)/1000000000f))+" ns too slow");
			}
			start = System.nanoTime();
			
			// Send data to renderclients and androids
			srv.androidSend();
			srv.rendererSend();
			
			// Purges dead clients
			purgeDead();
		}
	}

	/**
	 * Moves all entities according to their properties.
	 * 
	 */
	public void moveEverything()
	{
		
		// If planes are outside of playing area, sets their angle towards the middle
		Coord centre = getCentre();
		aIt = airplanes.listIterator();
		Airplane temp;
		while(aIt.hasNext())
		{
			temp = aIt.next();
			if(temp.getPos().distance(centre)>=maxDistance)
			{
				temp.setAngle(temp.getPos().getAngle(centre));
			}
		}
		
		// Move all planes
		aIt = airplanes.listIterator();
		while(aIt.hasNext())
		{
			aIt.next().move();
		}
		
		// Move all bullets
		bIt = bullets.listIterator();
		while(bIt.hasNext())
		{
			bIt.next().move();
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
		aIt = airplanes.listIterator();
		Airplane tempPlane;
		Bullet tempBullet;
		while(aIt.hasNext())
		{
			tempPlane = aIt.next();
			bIt = bullets.listIterator();
			while(bIt.hasNext())
			{
				tempBullet = bIt.next();
				// If plane is already dead, skip consequent calculations on plane
				if(tempPlane.getStatus()==-1) 
					break;
				// For every bullet that is still alive and not owned by the current plane, check for collision.
				if(tempBullet.getStatus()>=0 && tempPlane!=tempBullet.getOwner() && tempPlane.getPos().distance(tempBullet.getPos())<planeHitbox)
				{
					if(tempPlane.hit()) // Register a hit, if true plane has been killed.
					{
						tempBullet.getOwner().incrementKills();
					}
					tempBullet.getOwner().incrementHits();
					tempBullet.setStatus(-1); // Set status of bullet as a hit. (Not alive anymore)
				}
			}
		}
	}

	/**
	 * Gets centre of all airplanes.
	 * @return Coordinates for centre
	 */
	public Coord getCentre()
	{
		Coord tempC = new Coord(0,0);
		
		if(airplanes.size() >0)
		{
			Airplane tempA;
			aIt = airplanes.listIterator();
			while(aIt.hasNext())
			{
				tempA = aIt.next();
				tempC.x += tempA.getPos().x;
				tempC.y += tempA.getPos().y;
			}
			tempC.x /= airplanes.size();
			tempC.y /= airplanes.size();
		}
		return tempC;
	}
	
	
	public int nextAId()
	{
		return planeIdPool++;
	}
	
	public int nextBId()
	{
		return bulletIdPool++;
	}
	
	public void purgeDead()
	{
		aIt = airplanes.listIterator();
		Airplane tempA;
		while(aIt.hasNext())
		{
			tempA = aIt.next();
			if(tempA.getStatus()<0)
				aIt.remove();
			else if(tempA.getStatus()>0)
				tempA.setStatus(0);
		}
		bIt = bullets.listIterator();
		Bullet tempB;
		while(bIt.hasNext())
		{
			tempB = bIt.next();
			if(tempB.getStatus()<0)
				bIt.remove();
			else if(tempB.getStatus()>0)
				tempB.setStatus(0);
		}
	}
	
	public ListIterator<Airplane> getPlaneIterator()
	{
		return airplanes.listIterator();
	}
	
	public ListIterator<Bullet> getBulletIterator()
	{
		return bullets.listIterator();
	}
	
	public Airplane getPlaneById(int id)
	{
		aIt = airplanes.listIterator();
		Airplane tempA = null;
		while(aIt.hasNext())
		{
			tempA = aIt.next();
			if(tempA.getId()==id)
				break;
			tempA = null;
		}
		return tempA;
	}
}
