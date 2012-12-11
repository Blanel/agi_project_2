package agi_p2_server;

public class Bullet extends Entity {
	
	private Airplane owner;
	private final static double INITIAL_SPEED = 0.5; 
	private final static double ttl = 180;
	private double life=0;
	
	/*
	 * Statuses for bullets:
	 * 1 spawned
	 * 0 alive
	 * -1 hit
	 * -2 dead
	 */
	
	public Bullet(int id, Airplane owner)
	{
		super(id,owner.getPos().x, owner.getPos().y, owner.getAngle(), owner.getSpeed()+INITIAL_SPEED);
		
		this.owner = owner;
	}
	
	public void move()
	{
		if(++life == ttl)
		{
			setStatus(-2);
		}
		super.move();			
	}
	
	
	public Airplane getOwner()
	{
		return owner;
	}
	
	
	

}
