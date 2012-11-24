package com.example.agi_project_2_control;

import android.app.Activity;
import android.content.Context;
import android.graphics.Color;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
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
	/**
	 * Adding classes 
	 */
	private static Client client = new Client();	
	public static Airplane airplane = new Airplane();
	
	/**
	 * Image Viewers
	 */
	private ImageView fireImage;
	private ImageView gasImage;
	public ImageView viewBKImage;
	public ImageView viewLifeImage;
	public ImageView imageRedFlash; 
	public ImageView imageViewNavigation;
	public ImageView imageViewArrow;
	
	/**
	 * Used for sensor usage
	 */
	private SensorManager mSensorManager;
	private Sensor mAccelerometer;
	
	/*
	CustomDrawableView mCustomDrawableView = null;
    ShapeDrawable mDrawable = new ShapeDrawable();
	*/
	/**
	 * Screen size
	 */
	private int screenWidth;
	private int screenHeight;
	
	/**
	 * Is the android player alive
	 */
	public static boolean alive = true;

	
	private int lastFire = -1;
	private int lastGas = -1;
	private final Object touchMutex = new Object();

	/**
	 * Starting Threads
	 */
	private Thread threadImage;
	private Thread threadInput;
	
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
	
	/**
	 * Called when the activity first creates.
	 */
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		new GestureDetector(this);

		
		/**
		 * Sending Image size to server and client type in this case Android.
		 */
		Display display = getWindowManager().getDefaultDisplay(); 
		this.screenWidth = display.getWidth();
		this.screenHeight = display.getHeight();
		try {
			client.sendAction("Android");
			client.sendAction("screenWidth" + screenWidth);
			client.sendAction("screenHeight" + screenHeight);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		/*
		/**
		 * Initializing OpenGL
		 * 
		this.requestWindowFeature(Window.FEATURE_NO_TITLE); 
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
 		GLSurfaceView v = new GLSurfaceView(this);
   		v.setRenderer(new OpenGLRenderer());
   		setContentView(v);
		*/
		
		/**
		 * Images
		 */
		this.fireImage 				= (ImageView)findViewById(R.id.imageFire);
		this.gasImage 				= (ImageView)findViewById(R.id.imageGas);
		this.viewBKImage 			= (ImageView)findViewById(R.id.imageViewBK);
		this.viewLifeImage 			= (ImageView)findViewById(R.id.imageViewLife);
		this.imageRedFlash 			= (ImageView)findViewById(R.id.imageRedFlash);
		this.imageViewNavigation 	= (ImageView)findViewById(R.id.imageViewNavigation);
		this.imageViewArrow 		= (ImageView)findViewById(R.id.imageViewArrow);

		/**
		 * Accelerometer
		 */
		mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
		mAccelerometer = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
		mSensorManager.registerListener(this, mAccelerometer, SensorManager.SENSOR_DELAY_NORMAL);
		
		threadInput = new Thread(){
			@Override
			public void run(){
				while(true){
					try {
						client.reciveAction(airplane);
					}
					catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}
		};
		
		threadImage = new Thread(){
			@Override
			public void run(){
				while(true)
					try {
						Thread.sleep(100);
						(Message.obtain(MainActivity.this.mainHandler, 0)).sendToTarget();
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
			}
		};
        
		threadImage.setDaemon(true);
		threadImage.start();
		threadInput.setDaemon(true);
		threadInput.start();

	}
	/**
	 *	What should happen when the program needs to be resumed.
	 */
	protected void onResume() {
		super.onResume();
		mSensorManager.registerListener(this, mAccelerometer, SensorManager.SENSOR_DELAY_NORMAL);
	}
	/**
	 *	What should happen when the program is stopped being paused.
	 */
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
	
	public float rotation = 0; 
	/*
	private static final int[] rotationImagesXPositiv = {
		R.drawable.a352, R.drawable.a345, R.drawable.a337, R.drawable.a330,
		R.drawable.a322, R.drawable.a315, R.drawable.a307, R.drawable.a300,
		R.drawable.a292, R.drawable.a285, R.drawable.a277, R.drawable.a270,
		R.drawable.a0,   R.drawable.a7,   R.drawable.a15,  R.drawable.a22, 
		R.drawable.a30,  R.drawable.a37,  R.drawable.a45,  R.drawable.a52,
		R.drawable.a60,  R.drawable.a67,  R.drawable.a75,  R.drawable.a82, 
		R.drawable.a90
	};
	private static final int[] rotationImagesXNegative = {
		R.drawable.a97,  R.drawable.a105, R.drawable.a112, R.drawable.a120,
		R.drawable.a127, R.drawable.a135, R.drawable.a142, R.drawable.a150,
		R.drawable.a157, R.drawable.a165, R.drawable.a172, R.drawable.a180,
		R.drawable.a187, R.drawable.a195, R.drawable.a202, R.drawable.a210,
		R.drawable.a217, R.drawable.a225, R.drawable.a232, R.drawable.a240,
		R.drawable.a247, R.drawable.a255, R.drawable.a262
	};
	*/
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
			client.sendAction("x"+Float.toString(x));
			client.sendAction("y"+Float.toString(y));
			//client.sendAction("z"+Float.toString(z));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		/*
		if (x <= 0.0f){
			if (y > 9.2f){
				;
				//this.imageViewArrow.setImageResource(rotationImagesXPositiv[0]);
			}
			int n = 24;
			for(int i = 1; i < n ; i++){
				if(y > -9.2f*i && y <= -8.4f*i){
					;
					//this.imageViewArrow.setImageResource(rotationImagesXPositiv[i]);
				}
			}
			if (y < -9.2f){
				;
				//this.imageViewArrow.setImageResource(rotationImagesXPositiv[24]);
			}
		}*/
	}
	
	@Override
    public boolean onTouchEvent(MotionEvent e){
		synchronized (this.touchMutex){
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
	public boolean onFling(MotionEvent arg0, MotionEvent arg1, float arg2,
			float arg3) {
		// TODO Auto-generated method stub
		return false;
	}
	@Override
	public void onLongPress(MotionEvent arg0) {
		// TODO Auto-generated method stub
	}
	@Override
	public boolean onScroll(MotionEvent arg0, MotionEvent arg1, float arg2,
			float arg3) {
		// TODO Auto-generated method stub
		return false;
	}
	@Override
	public void onShowPress(MotionEvent arg0) {
		// TODO Auto-generated method stub
	}
	@Override
	public boolean onSingleTapUp(MotionEvent arg0) {
		// TODO Auto-generated method stub
		return false;
	}
	@Override
	public boolean onTouch(View arg0, MotionEvent arg1) {
		// TODO Auto-generated method stub
		return false;
	}
	
	private boolean isHit = false;
	private int isHitNumber = 5;
	private long endFlash = 0;
	private static final int[] lifeResources = { R.drawable.life, R.drawable.life1, R.drawable.life2, R.drawable.life3, R.drawable.life4 }; 
	
	private void lifeSpan() {
		
		if (airplane.life != isHitNumber){
			this.viewLifeImage.setImageResource(lifeResources[airplane.life]);
			this.imageRedFlash.setBackgroundColor(Color.parseColor("#86E00000"));
			isHit = true;
			isHitNumber = airplane.life;
			if (isHitNumber != 0){
				endFlash = System.currentTimeMillis() + 300;
				(new Thread(){
					@Override
					public void run(){
						try {
							while (System.currentTimeMillis() < endFlash)
								Thread.sleep(endFlash - System.currentTimeMillis());
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
						(Message.obtain(MainActivity.this.mainHandler, 1)).sendToTarget();
					}
				}).start();
			}
		}
    }
	private void endFlash()
	{
		imageRedFlash.setBackgroundColor(Color.parseColor("#00E00000"));
		isHit = false;
	}
	public void  setRenderer(GLSurfaceView.Renderer renderer){	
	}
	public Handler mainHandler = new Handler() {
        public void handleMessage(android.os.Message msg) {
            if (msg.what == 0) {
            	lifeSpan();
            }
            if (msg.what == 1) {
            	endFlash();
            }
            //if (mag.what == 2) {
            	//reverseLandscape();
            //}
        };
    };  
}


