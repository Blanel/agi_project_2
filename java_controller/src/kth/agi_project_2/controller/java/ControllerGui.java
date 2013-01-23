/**
 * Unused begining to a gui for the controller. 
 * Works with arrowkeys and spacebar for shooting.
 * No graphics shown in controller
 * @author Eric Nellåker
 */

package kth.agi_project_2.controller.java;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class ControllerGui extends JFrame implements KeyListener {
	
	private JavaController jc;
	
	private JPanel contentPane;
	
	private static final int KEY_SHOOTING = 32;
	private static final int KEY_ACCELERATOR = 38;
	private static final int KEY_LEFT =37;
	private static final int KEY_RIGHT = 39;
	public JLabel life;
	
	public static void main(String[] args)
	{
		new ControllerGui();
	}
	
	private ControllerGui()
	{
		jc = new JavaController(this);
		this.addKeyListener(this);
		contentPane = new JPanel(new BorderLayout());
		populateContentPane();
		jc.setHost("localhost", 1234);
		jc.connect();
		this.setContentPane(contentPane);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.pack();
		this.setVisible(true);
	}
	
	private void populateContentPane()
	{
		life = new JLabel("5");
		
		JPanel west = new JPanel(new FlowLayout());
		
		west.add(new JLabel("Life: "));
		west.add(life);
		
		contentPane.add(west, BorderLayout.WEST);
	}

	// Keyboard releated
	public void keyPressed(KeyEvent arg0) {
		
		System.err.println(arg0.getKeyCode()); // TODO Handle key down events
		handleKey(arg0.getKeyCode(), true);
		
	}

	public void keyReleased(KeyEvent arg0) {
		// TODO Handle key up events
		handleKey(arg0.getKeyCode(), false);
		
	}
	
	private void handleKey(int key, boolean down)
	{
		if(key == KEY_SHOOTING)
		{
			jc.setShooting(down);
		}
		else if(key == KEY_ACCELERATOR)
		{
			jc.setSpeedFrac((down ? 1 : 0));
		}
		else if(key == KEY_LEFT)
		{
			jc.setRotation((down ? 1 : 0));
		}
		else if(key == KEY_RIGHT)
		{
			jc.setRotation((down ? -1 : 0));
		}
		
	}

	public void keyTyped(KeyEvent arg0) {
		// This probably won't be needed
		
	}

}
