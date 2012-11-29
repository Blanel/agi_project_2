package agi_p2_server;

public class Entity {
	private int id;
	private Coord pos;
	private double angle;
	
	private double speed;
	
	private int status;
	
	public Entity(int id, double x, double y, double angle, double speed)
	{
		this.id = id;
		pos = new Coord();
		pos.x = x;
		pos.y = y;
		this.angle = angle;
		this.speed = speed;
		status =1;
	}
	
	
	/**
	 * Moves entity according to inherent properties.
	 */
	public void move()
	{
		pos.x += speed*Math.cos(angle);
		pos.y += speed*Math.sin(angle);
	}
	
	public int getId()
	{
		return id;
	}
	
	public void setId(int id)
	{
		this.id=id;
	}
	
	public Coord getPos()
	{
		return pos;
	}
	
	public void setPos(double x, double y)
	{
		pos.x=x;
		pos.y=y;
	}
	
	public void setPos(Coord p)
	{
		pos.x = p.x;
		pos.y = p.y;
	}
	public double getAngle() 
	{
		return angle;
	}
	public void setAngle(double angle) 
	{
		this.angle = angle;
	}
	
	public void addAngle(double angle)
	{
		this.angle += angle;
	}
	public double getSpeed() 
	{
		return speed;
	}
	public void setSpeed(double speed) 
	{
		this.speed = speed;
	}
	public int getStatus()
	{
		return status;
	}
	
	public void setStatus(int i)
	{
		status = i;
	}
	

}
