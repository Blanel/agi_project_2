package se.jonasandree.airbattles.server;

public class Bullet {
	private float positionX;
	private float positionY;
	private float rotation;
	private float speed = 2;
	private boolean exist = false;
	private int timeLeft = 200;
	public int bIndex;
	
	public Bullet(int bIndex,float positionX,float positionY,float rotation ){
		this.bIndex = bIndex;
		this.positionX = (float) (positionX + speed*Math.cos(this.rotation*Math.PI/180)*0.2);
		this.positionY = (float) (positionY + speed*Math.sin(this.rotation*Math.PI/180)*0.2);
		this.rotation = rotation;
		this.exist = true;
	}
	public float getPositionX(){
		return this.positionX;
	}
	public float getPositionY(){
		return this.positionY;
	}
	public float getRotation(){
		return this.rotation;
	}
	public boolean getExist(){
		return this.exist;
	}
	public void uppdatePosition(){
		if (timeLeft>0){
			this.positionX = (float) (this.positionX + speed*Math.cos(this.rotation*Math.PI/180)*0.2);
			this.positionY = (float) (this.positionY + speed*Math.sin(this.rotation*Math.PI/180)*0.2);
			this.timeLeft = this.timeLeft-1;
		}
		else{
			exist = false;
		}
	}
}
