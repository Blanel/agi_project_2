package com.example.agi_project_2_control;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.widget.Button;

import java.io.IOException;
import java.net.UnknownHostException;
import java.util.Date;


public class MainActivity extends Activity 
	implements View.OnClickListener {
	
	Button btn;
	
	@Override
	protected void onCreate(Bundle icicle) {
		super.onCreate(icicle);
		
		setContentView(R.layout.button);
		
		btn = (Button)findViewById(R.id.button);
		btn.setOnClickListener(this);
		updateTime();
		fireButton();
	}
	
	public void onClick(View view){
		fireButton();
	}

	private void fireButton(){
		try {
			(new Client()).connect();
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	private void updateTime(){
		btn.setText(new Date().toString());
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}

}
