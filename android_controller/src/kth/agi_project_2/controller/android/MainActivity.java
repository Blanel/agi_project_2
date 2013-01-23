/**
 * GUI for android controller
 * @author Jonas André, Eric Nellåker
 */

package kth.agi_project_2.controller.android;

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
import android.view.Display;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.VideoView;

import kth.agi_project_2.controller.android.R;

import android.view.GestureDetector.OnGestureListener;
import android.view.GestureDetector;

public final class MainActivity extends Activity
implements View.OnTouchListener, SensorEventListener, OnGestureListener {

	private AndroidController ac;

	/**
	 * Image Viewers
	 */
	private ImageView fireImage;
	private ImageView gasImage;

	private ImageView viewLifeImage;
	private ImageView imageRedFlash;
	private ImageView circle;

	private final int[] lifeResources = { R.drawable.life0, R.drawable.life1, R.drawable.life2, R.drawable.life3, R.drawable.life4, R.drawable.life5 }; 




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

	private int lastFire = -1;
	private int lastGas = -1;
	private final Object touchMutex = new Object();
	private boolean shootingToggle = false;
	private boolean shootingDown = false;	

	/**
	 * Video
	 */
	public VideoView viewBKVideo;
	private String srcPath = "android.resource://kth.agi_project_2/raw/introvideo";
	
	/**
	 * Sound
	 */
	private MediaPlayer backgroundMusic;
	private boolean musicOn = false;
	private int fireSoundPtr = 0;
	private int motorsSoundPtr = 0;
	private MediaPlayer[] fireSoundPool = new MediaPlayer[20];
	private MediaPlayer[] motorsSoundPool = new MediaPlayer[3];

	/**
	 * Starting Threads
	 */
	private boolean initialised = false;

	/**
	 * Called when the activity first creates.
	 */
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		ac = new AndroidController(this);
		
		final Context context = this;
		AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(
				context);

		// set title
		alertDialogBuilder.setTitle("Enter IP:port");
		final EditText input = new EditText(this);
		alertDialogBuilder.setView(input);

		// set dialog message
		alertDialogBuilder
		.setCancelable(false)
		.setPositiveButton("Yes",new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog,int id) {
				Editable hosttemp = input.getText();

				try {
					String host = hosttemp.toString().split(":")[0];
					int port = Integer.parseInt(hosttemp.toString().split(":")[1]);
					ac.setHost(host,port);
					initialised = ac.connect();
					continueRunning();
				}

				catch (ArrayIndexOutOfBoundsException e){
					e.printStackTrace();
				} catch (NumberFormatException e) {
					e.printStackTrace();
				}


			}
		});
		// create alert dialog
		AlertDialog alertDialog = alertDialogBuilder.create();
		// show it
		alertDialog.show();
	}

	public void continueRunning()
	{


		new GestureDetector(this);	
		showVideo();

		/**
		 * Sounds 
		 */
		backgroundMusic = MediaPlayer.create(this, R.raw.roxcity);
		backgroundMusic.setVolume(2.8f, 2.8f);
		if(musicOn)
			backgroundMusic.start();

		/**
		 * Sending Image size to server and client type in this case Android.
		 */
		Display display = getWindowManager().getDefaultDisplay(); 
		this.screenWidth = display.getWidth();
		this.screenHeight = display.getHeight();
		ac.setScreenHeight(screenHeight);

		/**
		 * Images
		 */
		this.fireImage 				= (ImageView)findViewById(R.id.imageFire);
		this.gasImage 				= (ImageView)findViewById(R.id.imageGas);
		this.viewLifeImage 			= (ImageView)findViewById(R.id.imageViewLife);
		this.imageRedFlash 			= (ImageView)findViewById(R.id.imageRedFlash);

		/**
		 * Accelerometer
		 */
		mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
		mAccelerometer = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
		mSensorManager.registerListener(this, mAccelerometer, SensorManager.SENSOR_DELAY_NORMAL);


		/*
		 * Thread that handles music. (maybe should be moved to an accessible thread)
		 */
		(new Thread(){
			@Override
			public void run(){
				while(ac.isAlive()){
					try {
						Thread.sleep(100);
						(Message.obtain(mainHandler, 0)).sendToTarget();
						if (!backgroundMusic.isPlaying() && musicOn)
							backgroundMusic.start();
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}
		}).start();

	}

	/**
	 *	What should happen when the program needs to be resumed.
	 */
	protected void onResume() {
		super.onResume();
		if(initialised)
			mSensorManager.registerListener(this, mAccelerometer, SensorManager.SENSOR_DELAY_NORMAL);
	}
	/**
	 *	What should happen when the program is stopped being paused.
	 */
	protected void onPause() {
		super.onPause();
		if(initialised)
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
	}
	/**
	 * Checking the accelerometer sensor for change and sends the change to the server and rotates the 
	 * arrow image at the screen.
	 */
	@Override
	public void onSensorChanged(SensorEvent event) {
		float x = event.values[0];
		float y = event.values[1];
		
		ac.setRotX(x);
		ac.setRotY(y);

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
			if ((fire != this.lastFire) && (fire != -1)){
				if (this.fireSoundPool[this.fireSoundPtr] == null)
					this.fireSoundPool[this.fireSoundPtr] = MediaPlayer.create(this, R.raw.shot);
				this.fireSoundPool[this.fireSoundPtr++].start();
				this.fireSoundPtr %= this.fireSoundPool.length;
				shootingToggle=true;
				
			}
			if (gas != this.lastGas){
				if(gas !=-1)
					ac.setSpeedFrac(1-e.getY()/(double)screenHeight);
				else
					ac.setSpeedFrac(0);
			}
			if(shootingToggle && !shootingDown)
			{
				ac.setShooting(true);
				shootingDown = true;
			}
			else
			{
				shootingDown = false;
			}
			shootingToggle = false;
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

	public void lifeSpan() {	
		this.viewLifeImage.setImageResource(lifeResources[ac.getLife()]);
		imageRedFlash.setBackgroundColor(Color.parseColor("#86E00000"));
		(new Thread(){
			@Override
			public void run(){
				try {
					
					Thread.sleep(300);
					
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				(Message.obtain(mainHandler, 2)).sendToTarget();
			}
		}).start();
	}
	
	private void endFlash()
	{
		imageRedFlash.setBackgroundColor(Color.parseColor("#00E00000"));
	}

	public void  setRenderer(GLSurfaceView.Renderer renderer){	
	}
	
	private void showVideo(){
		VideoView vd = (VideoView)findViewById(R.id.videoViewBK);
		Uri uri = Uri.parse(srcPath);
		vd.setVideoURI(uri);
		vd.start();;
	}
	public Handler mainHandler = new Handler() {
        public void handleMessage(android.os.Message msg) {
            if (msg.what == 1) {
            	lifeSpan();
            }
            if (msg.what == 2) {
            	endFlash();
            }
        };
    }; 
}


