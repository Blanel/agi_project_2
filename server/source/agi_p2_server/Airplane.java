package agi_p2_server;

public class Airplane extends Entity{
	
	private int life;
	private int hits;
	private int kills;
	private String name;
	private int gear;
	private final static double[] speeds = {1,2,3,4};
	private AndroidClient owner;
	
	/*
	 * Statuses for planes:
	 * 1 = spawned
	 * 0 = alive
	 * -1 = dead
	 */
	
	public Airplane(int id, double x, double y, double angle,AndroidClient owner, String name)
	{
		
		super(id, x,y,angle, speeds[0]);
		gear = 0;
		this.name = name;
		life = 5;
		this.owner = owner;
	}
	public Airplane(int id, double x, double y, double angle, AndroidClient owner)
	{
		
		super(id, x,y,angle, speeds[0]);
		
		name = "John Doe";
		life = 5;
		this.owner = owner;
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
	
	public int getHits() 
	{
		return hits;
	}
	
	public void incrementHits()
	{
		hits++;
	}
	public int getKills() 
	{
		return kills;
	}
	public void incrementKills()
	{
		kills++;
	}
	public int getLife() 
	{
		return life;
	}
	public void setLife(int life) 
	{
		this.life = life;
	}
	
	public String getName() 
	{
		return name;
	}
	
	public void gearUp()
	{
		gear = (gear+1)%4;
		setSpeed(speeds[gear]);
	}

	
	

}
