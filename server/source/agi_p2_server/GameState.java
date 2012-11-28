package agi_p2_server;
import java.util.ArrayList;

public class GameState {
	
	
	private ArrayList<Airplane> airplanes;
	private ArrayList<Bullet> bullets;
	
	private static final double planeHitbox = 0.5f;
	
	public GameState()
	{
		airplanes = new ArrayList<Airplane>();
		bullets = new ArrayList<Bullet>();
	}
	
	public void calculateCollisions()
	{
		for(int i = 0 ; i<airplanes.size(); i++)
		{
			for(int j = 0 ; j<bullets.size() ; j++)
			{
				if(airplanes.get(i)!=bullets.get(j).getOwner() && airplanes.get(i).distance(bullets.get(j))<planeHitbox)
				{
					if(airplanes.get(i).hit())
					{
						bullets.get(j).getOwner().incrementKills();
					}
					bullets.get(j).getOwner().incrementHits();
					bullets.remove(j);
					j--;
				}
			}
		}
	}
	
	
	
	

}
