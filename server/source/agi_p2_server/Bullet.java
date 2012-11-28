package agi_p2_server;

public class Bullet extends Entity {
	
	private Airplane owner;
	private final static double INITIAL_SPEED = 10; 
	private final static double ttl = 10;
	private double life=0;
	private boolean exists=true;
	
	public Bullet(Airplane owner)
	{
		super(owner.getX(), owner.getY(), owner.getAngle(), owner.getSpeed()+INITIAL_SPEED);
		
		this.owner = owner;
	}
	
	public void move()
	{
		super.move();
		life++;
		if(life == ttl)
			exists=false;
			
	}
	
	public Airplane getOwner()
	{
		return owner;
	}
	
	
	

}
