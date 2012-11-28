package agi_p2_server;

public class Bullet extends Entity {
	
	private Airplane owner;
	private final static float INITIAL_SPEED = 10; 
	
	public Bullet(Airplane owner)
	{
		super(owner.getX(), owner.getY(), owner.getAngle(), owner.getSpeed()+INITIAL_SPEED);
		
		this.owner = owner;
	}
	
	

}
