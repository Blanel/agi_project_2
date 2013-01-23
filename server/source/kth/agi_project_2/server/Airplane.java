/**
 * Holds all useful information about each airplane entity
 * @author Eric Nell�ker
 */

package kth.agi_project_2.server;

public class Airplane extends Entity{
	
	private int life;
	private int hits;
	private int kills;
	private String name;
	
	
	public Airplane(int id, double x, double y, double angle, GameState gs)
	{
		super(id, x,y,angle, gs);	
		setSpeed(gs.planeBaseSpeed);
		name = "John Doe";
		life = gs.planeBaseLife;
	}
	

	/**
	 * Registers a hit on the plane.
	 * Updates status if plane is killed
	 * @return true if plane is dead after hit, false if plane is alive after hit
	 */
	public boolean hit()
	{
		if(--life==0)
		{
			setStatus(-1);
			return true;
		}
		return false;
	}
	
	/**
	 * Gets how many successful hits the airplane has made on opponents
	 * @return
	 */
	public int getHits() 
	{
		return hits;
	}
	
	/**
	 * Increments the amount of hits the airplane has made on opponents score by 1.
	 */
	public void incrementHits()
	{
		hits++;
	}
	
	/**
	 * Gets how many successful kills the airplane has made on opponents
	 * @return
	 */
	public int getKills() 
	{
		return kills;
	}
	
	/**
	 * Increments the amount of kills the airplane has made on opponents score by 1.
	 */
	public void incrementKills()
	{
		kills++;
	}
	
	/**
	 * Gets the airplanes life
	 * @return
	 */
	public int getLife() 
	{
		return life;
	}
	
	/**
	 * Sets the airplanes life
	 * @param life
	 */
	public void setLife(int life) 
	{
		this.life = life;
	}
	
	/**
	 * Returns the airplanes name
	 * @return
	 */
	public String getName() 
	{
		return name;
	}
	
	/**
	 * Modifies the speed
	 * @param m
	 */
	public void speedMod(double m)
	{
		setSpeed(gs.planeBaseSpeed+m*gs.planeModSpeed);
	}
	
}
