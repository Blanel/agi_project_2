package com.example.agi_project_2_control;

import android.app.Activity;
import android.content.Context;
import android.graphics.Color;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.view.Display;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.View;
import android.widget.ImageView;
import java.io.*;
import java.net.*;
import android.view.GestureDetector.OnGestureListener;
import android.view.GestureDetector;



public final class MainActivity extends Activity 
	implements View.OnTouchListener, SensorEventListener, OnGestureListener {
	private static Client client = new Client();	
	
	private ImageView fireImage;
	private ImageView gasImage;
	private ImageView viewBKImage;
	
	private SensorManager mSensorManager;
	private Sensor mAccelerometer;
	private int screenWidth;
	private int screenHeight;
	
	private GestureDetector gestureScanner;
	
	/**
	 * Server connect
	 */
	static{
		try {
			client.connect();
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		gestureScanner = new GestureDetector(this);
		
		this.fireImage = (ImageView)findViewById(R.id.imageFire);
		
		Display display = getWindowManager().getDefaultDisplay(); 
		this.screenWidth = display.getWidth();
		this.screenHeight = display.getHeight();
		
		try {
			client.sendAction("screenWidth: " + screenWidth + " screenHeight: " + screenHeight);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		
		this.gasImage = (ImageView)findViewById(R.id.imageGas);
		this.viewBKImage = (ImageView)findViewById(R.id.imageViewBK);
		
		/**
		 * Accelerometer
		 */
		mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
		mAccelerometer = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
		mSensorManager.registerListener(this, mAccelerometer, SensorManager.SENSOR_DELAY_NORMAL);
	}
	protected void onResume() {
		super.onResume();
		mSensorManager.registerListener(this, mAccelerometer, SensorManager.SENSOR_DELAY_NORMAL);
	}
	protected void onPause() {
		super.onPause();
		mSensorManager.unregisterListener(this);
	}
	
	/**
	 * Option menu
	 */
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}
	@Override
	public void onAccuracyChanged(Sensor sensor, int accuracy) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void onSensorChanged(SensorEvent event) {
		float x = event.values[0];
		float y = event.values[1];
		float z = event.values[2];
		
		try {
			client.sendAction("x :"+Float.toString(x)+" y :"+Float.toString(y)+ " z :"+Float.toString(z));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
			
	}
	
	
	private int lastFire = -1;
	private int lastGas = -1;
	private final Object touchMutex = new Object();
	
	@Override
    public boolean onTouchEvent(MotionEvent e)
    {
		synchronized (this.touchMutex)
		{
			int fire = -1, gas = -1;
			int n = e.getPointerCount();
			for (int i = 0; i < n; i++) {
			    float x = e.getX(i);
			    if (x < (int)(this.screenWidth*0.5)){
			    	gasImage.setBackgroundColor(Color.parseColor("#86E0AC00"));
			    	gas = i;
			    }
			    else {
			    	fire = i;
			    	fireImage.setBackgroundColor(Color.parseColor("#86E0AC00"));
				}
			}
			
			if ((e.getAction() == 1) || (e.getAction() == gas * 256 + 6)){
				gas = -1;
				gasImage.setBackgroundColor(Color.parseColor("#8600ACE0"));
			}
			
			if ((e.getAction() == 1) || (e.getAction() == fire * 256 + 6)){
				fire = -1;
				fireImage.setBackgroundColor(Color.parseColor("#8600ACE0"));
			}
			
			String msg = "";
			if ((fire != this.lastFire) && (fire != -1))
				msg += "fire\n";
			if (gas != this.lastGas)
				msg += gas != -1 ? "+gas\n" : "-gas\n";
			if (msg.isEmpty() == false)
				try {
					client.sendAction(msg + "\n");
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			
			this.lastGas = gas;
			this.lastFire = fire;
			
			return true;
		}
    }
	
	
	@Override
    public boolean onDown(MotionEvent e){
	return true;
    }

	@Override
    public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX, float velocityY){
		try {
			client.sendAction("-" + "FLING" + "-");
		} catch (IOException e11) {
			// TODO Auto-generated catch block
			e11.printStackTrace();
		}
        return true;
    }

    @Override
    public void onLongPress(MotionEvent e){
    	try {
			client.sendAction("-" + "LONG PRESS" + "-");
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
    }

    @Override
    public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX, float distanceY){
    	try {
			client.sendAction("-" + "SCROLL" + "-");
		} catch (IOException e11) {
			// TODO Auto-generated catch block
			e11.printStackTrace();
		}
        return true;
    }
    
    @Override
    public void onShowPress(MotionEvent e)
    {
    	try {
			client.sendAction("-" + "SHOW PRESS" + "-");
		} catch (IOException e11) {
			// TODO Auto-generated catch block
			e11.printStackTrace();
		}
    }    

    @Override
    public boolean onSingleTapUp(MotionEvent e){
    	try {
			client.sendAction("-" + "SINGLE TAP UP" + "-");
		} catch (IOException e11) {
			// TODO Auto-generated catch block
			e11.printStackTrace();
		}
        return true;
    }
	@Override
	public boolean onTouch(View v, MotionEvent event) {
		// TODO Auto-generated method stub
		return false;
	}	
	
}
