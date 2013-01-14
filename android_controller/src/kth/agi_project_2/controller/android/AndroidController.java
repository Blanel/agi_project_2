package kth.agi_project_2.controller.android;

import kth.agi_project_2.controller.AbstractController;
import android.os.Message;

public class AndroidController extends AbstractController {
	
	private MainActivity ma;
	// Hardware Variables
	private int screenHeight;
	private float rotX;
	private float rotY;
	
	public AndroidController(MainActivity ma)
	{
		super();
		this.ma = ma;
	}

	protected void lifeChangeEvent(int l) {
		(Message.obtain(ma.mainHandler, 1)).sendToTarget();
		
	}
	
	public int getScreenHeight() {
		return screenHeight;
	}

	public void setScreenHeight(int screenHeight) {
		this.screenHeight = screenHeight;
	}
	
	protected double getRotation()
	{
		return ((Math.atan2(rotX, rotY)+Math.PI/2)*10/Math.PI);
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

}
