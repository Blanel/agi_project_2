package agi_p2_server;

public class Entity {
	private int id;
	private Coord pos;
	private double angle;
	
	private double speed;
	
	private int status;
	
	protected GameState gs;
	
	public Entity(int id, double x, double y, double angle, double speed, GameState gs)
	{
		this.id = id;
		pos = new Coord();
		pos.x = x;
		pos.y = y;
		this.angle = angle;
		this.speed = speed;
		status =1;
		this.gs = gs;
	}
	
	public Entity(int id, double x, double y, double angle, GameState gs)
	{
		this.id = id;
		pos = new Coord();
		pos.x = x;
		pos.y = y;
		this.angle = angle;
		status =1;
		this.gs = gs;
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
		this.angle %= Math.PI*2;
		if(this.angle<0)
			this.angle += Math.PI*2;
	}
	
	public void addAngle(double angle)
	{
		this.angle += angle;
		this.angle %= Math.PI*2;
		if(this.angle<0)
			this.angle += Math.PI*2;
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
