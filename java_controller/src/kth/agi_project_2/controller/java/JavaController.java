package kth.agi_project_2.controller.java;

import kth.agi_project_2.controller.AbstractController;

public class JavaController extends AbstractController {

	private ControllerGui cg;
	
	private int rotation;
	private final double rotD = 0.15;
	public JavaController(ControllerGui cg)
	{
		super();
		this.cg = cg;
		rotation = 0;
		
	}
	
	public JavaController()
	{
		
	}
	protected void lifeChangeEvent(int l) {
		System.err.println("Life has changed! New life: "+ l);

	}
	protected double getRotation() {
		return rotD*rotation;
	}
	
	public void setRotation(int i)
	{
		rotation = i;
	}

}
