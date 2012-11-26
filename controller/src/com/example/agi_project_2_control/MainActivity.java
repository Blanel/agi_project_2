package com.example.agi_project_2_control;

import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.Matrix;
import android.graphics.drawable.Drawable;
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
import android.view.Display;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.View;
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
	/**
	 * Image Viewers
	 */
	private ImageView fireImage;
	private ImageView gasImage;
	//public ImageView viewBKImage;

	public ImageView viewLifeImage;
	public ImageView imageRedFlash; 
	public ImageView imageViewNavigation;
	//public ImageView imageViewArrow;
	public ImageView circle;
	
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
		
		showVideo();
		
		
		//viewBKVideo = (VideoView) findViewById(R.id.videoViewBK);
		//viewBKVideo = MediaPlayer.create(this, R.raw.introvideo);
		//viewBKVideo.start();
		
		
		/**
		 * Sounds 
		 */
		backgroundMusic = MediaPlayer.create(this, R.raw.roxcity);
		//backgroundMusic.setLooping(true);
		backgroundMusic.start();
		
		
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
		//this.viewBKImage 			= (ImageView)findViewById(R.id.imageViewBK);
		this.viewLifeImage 			= (ImageView)findViewById(R.id.imageViewLife);
		this.imageRedFlash 			= (ImageView)findViewById(R.id.imageRedFlash);
		this.imageViewNavigation 	= (ImageView)findViewById(R.id.imageViewNavigation);
		//this.imageViewArrow 		= (ImageView)findViewById(R.id.imageViewArrow);

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
				while(true){
					try {
						Thread.sleep(100);
						(Message.obtain(MainActivity.this.mainHandler, 0)).sendToTarget();
						if (!backgroundMusic.isPlaying())
							backgroundMusic.start();
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
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
	/**
	 *	What should happen when the program needs to be resumed.
	 */
	protected void onResume() {
		super.onResume();
		//MediaPlayer backgroundMusic = MediaPlayer.create(this, R.raw.roxcity);
		//backgroundMusic.setLooping(true);
		//backgroundMusic.start();
		mSensorManager.registerListener(this, mAccelerometer, SensorManager.SENSOR_DELAY_NORMAL);
	}
	/**
	 *	What should happen when the program is stopped being paused.
	 */
	protected void onPause() {
		super.onPause();
		//MediaPlayer backgroundMusic = MediaPlayer.create(this, R.raw.roxcity);
		//backgroundMusic.setLooping(true);
		//backgroundMusic.start();
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
		float z = event.values[2];
		
		try {
			client.sendAction("x"+Float.toString(x));
			client.sendAction("y"+Float.toString(y));
			
			//client.sendAction("z"+Float.toString(z)); No need to send at the moment we do not need to use it.
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
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
/*
	private static MediaPlayer motorsStartSound;
	private static MediaPlayer motorsSound;
	private static MediaPlayer motorsEndSound;
*/
	
	private int fireSoundPtr = 0;
	private int motorsStartSoundPtr = 0;
	private int motorsEndSoundPtr = 0;
	private int motorsSoundPtr = 0;
	
	private MediaPlayer[] fireSoundPool = new MediaPlayer[10];
	private MediaPlayer[] motorsStartSoundPool = new MediaPlayer[3];
	private MediaPlayer[] motorsEndPool = new MediaPlayer[3];
	private MediaPlayer[] motorsSoundPool = new MediaPlayer[3];
	
	@Override
    public boolean onTouchEvent(MotionEvent e){

		//MediaPlayer fireSounds = MediaPlayer.create(this, R.raw.shot);
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
				
				msg += "fire\n";
			}
			if (gas != this.lastGas){
				msg += gas != -1 ? "+gas"+e.getY()+"\n" : "-gas\n";
				/*
				if (msg.equals("+gas")){
			    	if (this.motorsStartSoundPool[this.motorsStartSoundPtr] == null)
						this.motorsStartSoundPool[this.motorsStartSoundPtr] = MediaPlayer.create(this, R.raw.motorsstart);
					this.motorsStartSoundPool[this.motorsStartSoundPtr++].start();
					this.motorsStartSoundPtr %= this.motorsStartSoundPool.length;
				}
				if (msg.equals("-gas")){
					this.motorsStartSoundPool[this.motorsStartSoundPtr-1].stop();
			    	if (this.motorsEndPool[this.motorsEndSoundPtr] == null)
						this.motorsEndPool[this.motorsEndSoundPtr] = MediaPlayer.create(this, R.raw.motorsend);
					this.motorsEndPool[this.motorsEndSoundPtr++].start();
					this.motorsEndSoundPtr %= this.motorsEndPool.length;
				}*/
			}
			if (msg.isEmpty() == false){
				try {
					client.sendAction(msg + "\n");
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
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

	private String srcPath = "android.resource://com.example.agi_project_2_control/raw/introvideo";
	private void showVideo(){
		VideoView vd = (VideoView)findViewById(R.id.videoViewBK);
		Uri uri = Uri.parse(srcPath);
		//Uri uri = Uri.parse("android.resource://package/"+R.raw.introvideo);
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
            //if (mag.what == 2) {
            	//reverseLandscape();
            //}
        };
    };  
}


