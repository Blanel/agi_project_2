package com.example.agi_project_2_control;

public class Airplane {
	public int life;
	public boolean alive;
	
	public Airplane(){
		this.life = 5;
		this.alive = true;
	}
	
	public void hit(){
		if (alive){
			if (this.life > 0){
				this.life--;
			}
			else{ 
				this.alive = false;
				MainActivity.alive = this.alive;
			}
		}
	}
}