package com.example.agi_project_2_control;

public class StateSender implements Runnable{
	
	private float speedFrac;
	private int screenHeight;
	private boolean shooting;
	private float rotX;
	private float rotY;
	
	public StateSender()
	{
		speedFrac = 0;
		shooting = false;
		screenHeight = 1;
		rotX = 0;
		rotY = 0;
	}
	
	public StateSender(int h)
	{
		speedFrac = 0;
		shooting = false;
		screenHeight = h;
		rotX = 0;
		rotY = 0;
	}
	

	public float getSpeedFrac() {
		return speedFrac;
	}

	public void setSpeedFrac(float speedFrac) {
		this.speedFrac = speedFrac;
	}

	public int getScreenHeight() {
		return screenHeight;
	}

	public void setScreenHeight(int screenHeight) {
		this.screenHeight = screenHeight;
	}

	public boolean isShooting() {
		return shooting;
	}

	public void setShooting(boolean shooting) {
		this.shooting = shooting;
	}

	public float getRotX() {
		return rotX;
	}

	public void setRotX(float rotX) {
		this.rotX = rotX;
	}

	public float getRotY() {
		return rotY;
	}

	public void setRotY(float rotY) {
		this.rotY = rotY;
	}
	
	public void run()
	{
		while(true) //TODO Create sane thread management here!
		{
			
		}
	}
	
	

}
