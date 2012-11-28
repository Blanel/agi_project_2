package agi_p2_server;

public class Airplane extends Entity{
	
	private int life;
	private int hits;
	private int kills;
	private String name;
	private final static double INITIAL_SPEED = 1;
	
	/*
	 * Statuses for planes:
	 * 1 = spawned
	 * 0 = alive
	 * -1 = dead
	 */
	
	public Airplane(int id, double x, double y, double angle, String name)
	{
		
		super(id, x,y,angle, INITIAL_SPEED);
		
		this.name = name;
		life = 5;
	}
	
	public boolean hit()
	{
		if(--life==0)
			return true;
		return false;
	}
	
	public void incrementHits()
	{
		hits++;
	}
	public void incrementKills()
	{
		kills++;
	}

	
	

}
