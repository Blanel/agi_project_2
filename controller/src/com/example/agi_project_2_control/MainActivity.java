package com.example.agi_project_2_control;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.widget.Button;

import java.io.*;
import java.net.*;

public class MainActivity extends Activity 
	implements View.OnClickListener {
	
	private Button fireButton;
	private Button gasButton;
	private static Client client = new Client();	
	
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
		
		this.fireButton = (Button)findViewById(R.id.button);
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
		this.fireButton.setText("Fire");
		
		this.gasButton = (Button)findViewById(R.id.button01);
		this.gasButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				try {
					gas();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
			}
		});
		this.gasButton.setText("Gas");		

	}
	


	private void fire() throws IOException{
		client.sendAction("fire");
	}
	private void gas() throws IOException{
		client.sendAction("gas");
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

}
