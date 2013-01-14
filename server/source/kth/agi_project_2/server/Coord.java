package kth.agi_project_2.server;

public class Coord
{
	public double x;
	public double y;
	
	public Coord()
	{
		x =0;
		y=0;
	}
	
	public Coord(double x, double y)
	{
		this.x = x;
		this.y = y;
	}
	
	public Coord(Coord pos)
	{
		x = pos.x;
		y = pos.y;
	}
	
	public double distance(Coord point)
	{
		return Math.sqrt((point.x-x)*(point.x-x)+(point.y-y)*(point.y-y));
	}
	
	public double getAngle(Coord point)
	{
		Coord temp = new Coord(point);
		temp.x -=x;
		temp.y -=y;
		return Math.atan2(temp.y, temp.x);
	}
}
