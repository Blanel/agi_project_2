package agi_p2_server;

public class Airplane extends Entity{
	
	private int life;
	private int hits;
	private int kills;
	private String name;
	
	private final static double BASESPEED = 0.01;
	private final static double SPM = 0.01;
	
	/*
	 * Statuses for planes:
	 * 1 = spawned
	 * 0 = alive
	 * -1 = dead
	 */
	
	public Airplane(int id, double x, double y, double angle, String name)
	{
		super(id, x,y,angle, BASESPEED);
		this.name = name;
		life = 5;
	}
	public Airplane(int id, double x, double y, double angle)
	{
		super(id, x,y,angle, BASESPEED);	
		name = "John Doe";
		life = 5;
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
		setSpeed(BASESPEED+m*SPM);
	}
}
