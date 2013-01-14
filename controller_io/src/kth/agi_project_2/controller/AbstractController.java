package kth.agi_project_2.controller;

public abstract class AbstractController {
	
	private ServerIO sio;
	public AbstractController()
	{
		sio = new ServerIO(this);
	}
	
	protected abstract void lifeChangeEvent(int l);
	
	protected abstract double getRotation();
	
	public void setSpeedFrac(double speedFrac)
	{
		sio.setSpeedFrac(speedFrac);
	}
	public void setShooting(boolean shooting)
	{
		sio.setShooting(shooting);
	}
	public int getLife()
	{
		return sio.getLife();
	}
	public boolean connect()
	{
		return sio.connect();
	}
	public void setHost(String host, int port)
	{
		sio.setHost(host, port);
	}
	public boolean isAlive()
	{
		return sio.isAlive();
	}
	
	
	
	

}
