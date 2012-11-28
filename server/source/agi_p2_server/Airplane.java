package agi_p2_server;

public class Airplane extends Entity{
	
	private int life;
	private int hits;
	private int kills;
	private String name;
	private boolean isShooting;
	private boolean isSwitchingGears;
	private final static double INITIAL_SPEED = 1;
	
	public Airplane(double x, double y, double angle, String name)
	{
		super(x,y,angle, INITIAL_SPEED);
		
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
