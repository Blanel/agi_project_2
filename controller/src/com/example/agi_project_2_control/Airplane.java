package com.example.agi_project_2_control;

import android.os.Message;

public class Airplane {
	private int life;
	private MainActivity act;
	public Airplane(MainActivity act){
		this.act = act;
		this.life = 5;
	}
	
	public void setLife(int l)
	{
		life = l;
		(Message.obtain(act.mainHandler, 1)).sendToTarget();
	}
	
	public int getLife()
	{
		return life;
	}
	
	public boolean isAlive(){
		return (life>0);
	}
}