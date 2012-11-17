package com.example.agi_project_2_control;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.widget.Button;

import java.io.*;
import java.net.*;
import java.util.Date;

public class MainActivity extends Activity 
	implements View.OnClickListener {
	
	private Button fireButton;
	private Client client = new Client();
	
	@Override
	protected void onCreate(Bundle icicle) {
		super.onCreate(icicle);
		
		setContentView(R.layout.button);
		
		this.fireButton = (Button)findViewById(R.id.button);
		this.fireButton.setOnClickListener(this);
		updateTime();
		
		
		/**
		 * Server connect
		 */
		try {
			this.client.connect();
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
	public void onClick(View view){
		try {
			fire();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	private void fire() throws IOException{
		this.client.sendAction("fire");
	}
	
	private void updateTime(){
		this.fireButton.setText(new Date().toString());
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}

}
