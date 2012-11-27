package se.jonasandree.airbattles.server;

public class Bullet {
	private float positionX;
	private float positionY;
	private float rotation;
	private float directionX;
	private float directionY;
	private float speed = 2;
	private boolean exist = false;
	private int timeLeft = 20;
	
	public void setPositionX(float x){
		this.directionX = (float) (Math.cos(this.rotation*Math.PI/180))*speed;
		this.positionX = x + this.directionX;
	}
	public void setPositionY(float y){
		this.directionY = (float) (Math.sin(this.rotation*Math.PI/180))*speed;
		this.positionY = y + this.directionY;
	}
	public float getPositionX(){
		return this.positionX;
	}
	public float getPositionY(){
		return this.positionY;
	}
	public void setRotation(float r){
		this.rotation = r;
	}
	public float getRotation(){
		return this.rotation;
	}
	public void setExist(boolean exist){
		this.exist = exist;
	}
	public boolean getExist(){
		return this.exist;
	}
	public void uppdatePosition(){
		if (timeLeft>0){
			this.positionX = this.positionX + this.directionX;
			this.positionY = this.positionY + this.directionY;	
			this.timeLeft = this.timeLeft-1;
		}
		else{
			exist = false;
		}
	}
}
