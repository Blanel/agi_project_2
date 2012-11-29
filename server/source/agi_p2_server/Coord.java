package agi_p2_server;

public class Coord
{
	public double x;
	public double y;
	
	public double distance(Coord point)
	{
		return Math.sqrt((point.x-x)*(point.x-x)+(point.y-y)*(point.y-y));
	}
}
