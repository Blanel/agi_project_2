package com.example.agi_project_2_control;

import android.app.Activity;
import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.View;
import android.widget.ImageView;
import java.io.*;
import java.net.*;

public class MainActivity extends Activity 
	implements View.OnTouchListener, SensorEventListener {
	private static Client client = new Client();	
	
	private ImageView fireButton;
	private ImageView gasButton;
	private SensorManager mSensorManager;
	private Sensor mAccelerometer;
	
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
	protected void onCreate(Bundle icicle) {
		super.onCreate(icicle);
		setContentView(R.layout.activity_main);
		
		this.fireButton = (ImageView)findViewById(R.id.imageFire);
		
		/*
		this.fireButton.setOnTouchListener(new View.OnTouchListener() {
			@Override
			public boolean onTouch(View arg0, MotionEvent arg1) {			    
				if(arg1.getAction() == MotionEvent.ACTION_DOWN) {
					try {
						fire();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				return false;
			}
		});
		*/
		
		this.gasButton = (ImageView)findViewById(R.id.imageGas);
		
		
		/*
		this.gasButton.setOnTouchListener(new View.OnTouchListener() {
			@Override
			public boolean onTouch(View arg0, MotionEvent arg1) {
				if(arg1.getAction() == MotionEvent.ACTION_DOWN) {
					try {
						gas();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				else if(arg1.getAction() == MotionEvent.ACTION_UP) {
					try {
						noGas();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				return false;
				
			}
		});
		*/

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
	
	private void fire() throws IOException{
		client.sendAction("fire");
	}
	private void gas() throws IOException{
		client.sendAction("gas");
	}
	private void noGas() throws IOException{
		client.sendAction("noGas");
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
	
	
	@Override
	public boolean onTouch(View arg0, MotionEvent arg1) {
		// TODO Auto-generated method stub
		return false;
	}

}
