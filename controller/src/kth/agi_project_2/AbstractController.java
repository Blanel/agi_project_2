package kth.agi_project_2;

public abstract class AbstractController {
	
	private ServerIO sio;
	public AbstractController()
	{
		sio = new ServerIO(this);
	}
	
	protected abstract void lifeChangeEvent(int l);
	
	protected abstract double getRotation();
	
	protected void setSpeedFrac(double speedFrac)
	{
		sio.setSpeedFrac(speedFrac);
	}
	protected void setShooting(boolean shooting)
	{
		sio.setShooting(shooting);
	}
	protected int getLife()
	{
		return sio.getLife();
	}
	protected boolean connect()
	{
		return sio.connect();
	}
	protected void setHost(String host, int port)
	{
		sio.setHost(host, port);
	}
	protected boolean isAlive()
	{
		return sio.isAlive();
	}
	
	
	
	

}
