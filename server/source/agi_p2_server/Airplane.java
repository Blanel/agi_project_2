package agi_p2_server;

public class Airplane extends Entity{
	
	private int life;
	private int hits;
	private int kills;
	private String name;
	private boolean isShooting;
	private boolean isSwitchingGears;
	private final static float INITIAL_SPEED = 1;
	
	public Airplane(float x, float y, float angle, String name)
	{
		super(x,y,angle, INITIAL_SPEED);
		
		this.name = name;
		life = 5;
	}

	
	

}
