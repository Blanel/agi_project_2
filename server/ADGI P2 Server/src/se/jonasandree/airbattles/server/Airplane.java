package se.jonasandree.airbattles.server;

public class Airplane {
	private int index;
	private float rotationX 		= 0;
	private float rotationY 		= 0;
	private float rotation 			= (float) Math.random()*360;
	private float positionX			= 0;
	private float positionY			= 0;
	private float speed				= 0;
	private int life				= 5;
	private boolean alive			= true;
	private float maxVelocity		= (float) 20.0;
	private float velocity 			= 1;
	private boolean gas 			= false;
	private double velocityDecrese 	= 0.5;
	public Bullet bullets[] 		= new Bullet[1024];
	
	public Airplane(int index){
		this.index = index;
	}
	public void hit(){
		if (alive){
			if (this.life > 0){
				this.life--;
			}
			else{ 
				this.alive = false;
			}
		}
	}
	public void setSpeed(float speed){
		this.speed = speed;
		this.gas = true;
		this.maxVelocity = speed*20;
		
		System.out.println(this.velocity +" v "+ " mv " +this.maxVelocity);
		if (this.velocity <= this.maxVelocity){
			System.out.println(this.speed +" s "+ " v " +this.velocity);
			this.velocity = this.speed + this.velocity;
		}
	}
	public void uppdateSpeed(){
		if (this.velocity <= this.maxVelocity){
			System.out.println(this.speed +" s "+ " v " +this.velocity);
			this.velocity = this.speed + this.velocity;
		}
	}
	public void noGas(){
		this.gas = false;
	}
	public void uppdateGas(){
		if (!this.gas){
			if (this.velocity > 1){
				this.velocity = (float) (this.velocity - this.velocityDecrese);
			}
			else{
				this.velocity = 1;
			}
		}
	}
	public void setRotationX(float x){
		this.rotationX = x;
	}
	public void setRotationY(float y){
		this.rotationY = y;
	}
	public float getRotation(){
		this.rotation = this.rotation + (float) -((Math.atan2(rotationX, rotationY)+Math.PI/2)*10/Math.PI);
		if (this.rotation > 360)
			this.rotation = this.rotation - 360;
		if (this.rotation < -360)
			this.rotation = this.rotation + 360;
		return this.rotation;
	}
	public float getPositionX(){
		this.positionX = (float) (this.velocity*Math.cos(this.rotation*Math.PI/180)*0.2)+this.positionX;
		return this.positionX;
	}
	public float getPositionY(){
		this.positionY = (float) (this.velocity*Math.sin(this.rotation*Math.PI/180)*0.2)+this.positionY;
		return this.positionY;
	}
	public float getVelocity(){
		return this.velocity;
	}
	public float getSpeed(){
		return this.speed;
	}
	public int getIndex(){
		return this.index;
	}
	public boolean getAlive(){
		return this.alive;
	}
	public void addBullets(int bIndex){
		bullets[bIndex] = new Bullet();
		bullets[bIndex].setExist(true);
		bullets[bIndex].setPositionX(this.rotation);
		bullets[bIndex].setPositionX((float) (this.positionX));
		bullets[bIndex].setPositionX((float) (this.positionX+Math.cos(this.rotation*Math.PI/180)*2));
	}
	public Bullet getBullets(int bulletIndex){
		return this.bullets[bulletIndex];
	}
}