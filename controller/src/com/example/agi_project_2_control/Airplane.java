package com.example.agi_project_2_control;

public class Airplane {
	private int life;
	public Airplane(){
		this.life = 5;
	}
	
	public void setLife(int l)
	{
		life = l;
	}
	
	public int getLife()
	{
		return life;
	}
	
	public boolean isAlive(){
		return (life>0);
	}
}