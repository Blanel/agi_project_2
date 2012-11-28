package agi_p2_server;

public class Entity {
	private float x;
	private float y;
	private float angle;
	private float speed;
	private final static float INITIAL_SPEED=0;
	
	public Entity(float x, float y, float angle, float speed)
	{
		this.x = x;
		this.y = y;
		this.angle = angle;
		this.speed = speed;
	}
	public void move()
	{
		x += speed*Math.cos(angle);
		y += speed*Math.sin(angle);
	}
	public float getX() {
		return x;
	}
	public void setX(float x) {
		this.x = x;
	}
	public float getY() {
		return y;
	}
	public void setY(float y) {
		this.y = y;
	}
	public float getAngle() {
		return angle;
	}
	public void setAngle(float angle) {
		this.angle = angle;
	}
	public float getSpeed() {
		return speed;
	}
	public void setSpeed(float speed) {
		this.speed = speed;
	}
	
	

}
