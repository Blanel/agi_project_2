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
import android.widget.ImageButton;


import java.io.*;
import java.net.*;

public class MainActivity extends Activity 
	implements View.OnClickListener, View.OnTouchListener, SensorEventListener {
	
	private ImageButton fireButton;
	private ImageButton gasButton;
	private static Client client = new Client();	
	
	private SensorManager mSensorManager;
	private Sensor mAccelerometer;
	
	static
	{
		/**
		 * Server connect
		 */
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
		
		this.fireButton = (ImageButton)findViewById(R.id.imageButtonFire);
		this.fireButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				try {
					fire();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
			}
		});
		//this.fireButton.setText("Fire");
		
		this.gasButton = (ImageButton)findViewById(R.id.imageButtonGas);
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
				if(arg1.getAction() == MotionEvent.ACTION_UP) {
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
	public void onAccuracyChanged1(Sensor sensor, int accuracy) {
		// can be safely ignored for this demo
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
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}

	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub
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
	

