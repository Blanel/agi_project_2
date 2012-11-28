package agi_p2_server;

public class Entity {
	private int id;
	private Coord pos;
	private double angle;
	
	private double speed;
	private final static double INITIAL_SPEED=0;
	
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
	
	public double getX() {
		return pos.x;
	}
	public void setX(double x) {
		pos.x = x;
	}
	public double getY() {
		return pos.y;
	}
	public void setY(double y) {
		pos.y = y;
	}
	public double getAngle() {
		return angle;
	}
	public void setAngle(double angle) {
		this.angle = angle;
	}
	public double getSpeed() {
		return speed;
	}
	public void setSpeed(double speed) {
		this.speed = speed;
	}
	
	private class Coord
	{
		public double x;
		public double y;
	}
	
	public double distance(Entity point)
	{
		return Math.sqrt((point.pos.x-pos.x)*(point.pos.x-pos.x)+(point.pos.y-pos.y)*(point.pos.y-pos.y));
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
