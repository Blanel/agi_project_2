package agi_p2_server;

public class Entity {
	private Coord pos;
	private double angle;
	private double speed;
	private final static double INITIAL_SPEED=0;
	
	public Entity(double x, double y, double angle, double speed)
	{
		pos.x = x;
		pos.y = y;
		this.angle = angle;
		this.speed = speed;
	}
	public void move()
	{
		pos.x += speed*Math.cos(angle);
		pos.y += speed*Math.sin(angle);
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
	

}
