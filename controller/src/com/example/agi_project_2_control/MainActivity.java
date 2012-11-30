package com.example.agi_project_2_control;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.Matrix;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.media.MediaPlayer;
import android.net.Uri;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.text.Editable;
import android.util.Log;
import android.view.Display;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.MediaController;
import android.widget.VideoView;

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
	
	private static StateSender ss = new StateSender();
	
	/**
	 * Image Viewers
	 */
	private ImageView fireImage;
	private ImageView gasImage;

	public ImageView viewLifeImage;
	public ImageView imageRedFlash; 
	public ImageView imageViewNavigation;
	public ImageView circle;
	
	
	
	/**
	 * Used for sensor usage
	 */
	private SensorManager mSensorManager;
	private Sensor mAccelerometer;
	
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
	 * Video
	 */
	public VideoView viewBKVideo;
	/**
	 * Sound
	 */
	private static MediaPlayer fireSounds;
	private static MediaPlayer backgroundMusic;
	private static MediaPlayer motorsStartSound;
	private static MediaPlayer motorsSound;
	private static MediaPlayer motorsEndSound;

	/**
	 * Starting Threads
	 */
	private Thread threadImage;
	private Thread threadInput;
	private Thread threadInputAlert;
	
	static boolean inititialised = false;
	public String host = "192.168.0.16";
	static boolean getHost = false;
		
	/**
	 * Called when the activity first creates.
	 */
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		/*
		if (getHost == false){
			final Context context = this;
	    	AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(
	    			context);
	    	
	    	// set title
	    	alertDialogBuilder.setTitle("Enter IP:");
	    	
	    	final EditText input = new EditText(this);
	    	alertDialogBuilder.setView(input);
	    	
	    	// set dialog message
	    	alertDialogBuilder
	    		.setCancelable(false)
	    		.setPositiveButton("Yes",new DialogInterface.OnClickListener() {
	    			public void onClick(DialogInterface dialog,int id) {
	    				Editable hosttemp = input.getText();
	    				host = hosttemp.toString();
	    				MainActivity.getHost = true;
	    			}
	    		  });

	    	// create alert dialog
	    	AlertDialog alertDialog = alertDialogBuilder.create();

	    	// show it
	    	alertDialog.show();
	    	Log.d("MyApp","1");
	    	MainActivity.getHost = true;
	    	
		}
		else{*/
			//Log.d("MyApp","1.5\n");
			if(inititialised == false){
				//Log.d("MyApp","2\n");
				try {
					client.connect(host);
				} catch (UnknownHostException e) {
					e.printStackTrace();
				} catch (IOException e) {
					e.printStackTrace();
				}
				inititialised = true;
			}
			//Log.d("MyApp","3\n");
			new GestureDetector(this);	
			showVideo();
	
			/**
			 * Sounds 
			 */
			backgroundMusic = MediaPlayer.create(this, R.raw.roxcity);
			backgroundMusic.setVolume(2.8f, 2.8f);
			backgroundMusic.start();
			
			
			/**
			 * Sending Image size to server and client type in this case Android.
			 */
			Display display = getWindowManager().getDefaultDisplay(); 
			this.screenWidth = display.getWidth();
			this.screenHeight = display.getHeight();
			
			ss.setScreenHeight(screenHeight);
			
			
			
			/*
			try {
				client.sendAction("Android");
				client.sendAction("screenWidth" + screenWidth);
				client.sendAction("screenHeight" + screenHeight);
			} catch (IOException e) {
				e.printStackTrace();
			}*/
			
			/**
			 * Images
			 */
			this.fireImage 				= (ImageView)findViewById(R.id.imageFire);
			this.gasImage 				= (ImageView)findViewById(R.id.imageGas);
			this.viewLifeImage 			= (ImageView)findViewById(R.id.imageViewLife);
			this.imageRedFlash 			= (ImageView)findViewById(R.id.imageRedFlash);
			this.imageViewNavigation 	= (ImageView)findViewById(R.id.imageViewNavigation);
	
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
							e.printStackTrace();
						}
					}
				}
			};
			/**
			 * Vad fan är det som händer egentligen
			 */
			threadImage = new Thread(){
				@Override
				public void run(){
					while(true){
						try {
							Thread.sleep(100);
							//(Message.obtain(MainActivity.this.mainHandler, 0)).sendToTarget();
							
							if (!backgroundMusic.isPlaying())
								backgroundMusic.start();
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
					}
				}
			};
	        
			threadImage.setDaemon(true);
			threadImage.start();
			threadInput.setDaemon(true);
			threadInput.start();
		}
		
	//}
	/**
	 *	What should happen when the program needs to be resumed.
	 */
	protected void onResume() {
		super.onResume();
		if(inititialised)
			mSensorManager.registerListener(this, mAccelerometer, SensorManager.SENSOR_DELAY_NORMAL);
	}
	/**
	 *	What should happen when the program is stopped being paused.
	 */
	protected void onPause() {
		super.onPause();
		if(inititialised)
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

	@Override
	public void onAccuracyChanged(Sensor sensor, int accuracy) {
		// TODO Auto-generated method stub
	}
	/**
	 * Checking the accelerometer sensor for change and sends the change to the server and rotates the 
	 * arrow image at the screen.
	 */
	@Override
	public void onSensorChanged(SensorEvent event) {
		float x = event.values[0];
		float y = event.values[1];
		//float z = event.values[2];
		
		/*try {
			client.sendAction("x"+Float.toString(x));
			client.sendAction("y"+Float.toString(y));
			
			//client.sendAction("z"+Float.toString(z)); No need to send at the moment we do not need to use it.
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}*/
		
		ss.setRotX(x);
		ss.setRotY(y);
		
		float degree = (float) (-Math.atan2(y/10, x/10)*180/Math.PI);
		
		circle = (ImageView) findViewById(R.id.imageViewArrow);
		Bitmap myImg = BitmapFactory.decodeResource(getResources(), R.drawable.a0);

		Matrix matrix = new Matrix(); 
		matrix.postRotate(degree);
		
		Bitmap rot = Bitmap.createBitmap(myImg, 0, 0, myImg.getWidth(), myImg.getHeight(), matrix, true);
		int off = (rot.getWidth() - myImg.getWidth()) / 2;
		Bitmap result = Bitmap.createBitmap(rot, off, off, myImg.getWidth(), myImg.getHeight());
		circle.setImageBitmap(result);
	}
	private int fireSoundPtr = 0;
	private int motorsStartSoundPtr = 0;
	private int motorsEndSoundPtr = 0;
	private int motorsSoundPtr = 0;
	
	private MediaPlayer[] fireSoundPool = new MediaPlayer[20];
	private MediaPlayer[] motorsStartSoundPool = new MediaPlayer[3];
	private MediaPlayer[] motorsEndPool = new MediaPlayer[3];
	private MediaPlayer[] motorsSoundPool = new MediaPlayer[3];
	
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
				    	if (this.motorsSoundPool[this.motorsSoundPtr] == null){
				    		this.motorsSoundPool[this.motorsSoundPtr] = MediaPlayer.create(this, R.raw.motors);
				    	}
			    		if(!motorsSoundPool[this.motorsSoundPtr].isPlaying()){
			    			this.motorsSoundPool[this.motorsSoundPtr++].start();
			    		}
						this.motorsSoundPtr %= this.motorsSoundPool.length;
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
			if ((fire != this.lastFire) && (fire != -1)){
				if (this.fireSoundPool[this.fireSoundPtr] == null)
					this.fireSoundPool[this.fireSoundPtr] = MediaPlayer.create(this, R.raw.shot);
				this.fireSoundPool[this.fireSoundPtr++].start();
				this.fireSoundPtr %= this.fireSoundPool.length;
				
				//msg += "fire\n";
				ss.setShooting(true);
			}
			if (gas != this.lastGas){
				//msg += gas != -1 ? "+gas"+e.getY()+"\n" : "-gas\n";
				ss.setSpeedFrac(e.getY());
			}
			/*if (msg.isEmpty() == false){
				try {
					client.sendAction(msg + "\n");
				} catch (IOException e1) {
					e1.printStackTrace();
				}
			}*/
			
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
		return false;
	}
	@Override
	public void onLongPress(MotionEvent arg0) {
	}
	@Override
	public boolean onScroll(MotionEvent arg0, MotionEvent arg1, float arg2,
			float arg3) {
		return false;
	}
	@Override
	public void onShowPress(MotionEvent arg0) {
	}
	@Override
	public boolean onSingleTapUp(MotionEvent arg0) {
		return false;
	}
	@Override
	public boolean onTouch(View arg0, MotionEvent arg1) {
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

	private String srcPath = "android.resource://com.example.agi_project_2_control/raw/introvideo";
	private void showVideo(){
		//Log.d("MyApp","ShowVideo\n");
		VideoView vd = (VideoView)findViewById(R.id.videoViewBK);
		Uri uri = Uri.parse(srcPath);
		vd.setVideoURI(uri);
		vd.start();;
	}
	
	
	
	public Handler mainHandler = new Handler() {
        public void handleMessage(android.os.Message msg) {
            if (msg.what == 0) {
            	lifeSpan();
            }
            if (msg.what == 1) {
            	endFlash();
            }
            if (msg.what == 2) {
            	inputhostID();
            }
        };
    }; 
    
    public void inputhostID(){
    	final Context context = this;
    	AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(
    			context);
    	
    	// set title
    	alertDialogBuilder.setTitle("Enter IP:");
    	
    	final EditText input = new EditText(this);
    	alertDialogBuilder.setView(input);
    	
    	// set dialog message
    	alertDialogBuilder
    		.setCancelable(false)
    		.setPositiveButton("Yes",new DialogInterface.OnClickListener() {
    			public void onClick(DialogInterface dialog,int id) {
    				Editable hosttemp = input.getText();
    				host = hosttemp.toString();
    				MainActivity.getHost = true;
    			}
    		  });

    	// create alert dialog
    	AlertDialog alertDialog = alertDialogBuilder.create();

    	// show it
    	alertDialog.show();
    	Log.d("MyApp","1");
    	MainActivity.getHost = true;
    }
    
}


