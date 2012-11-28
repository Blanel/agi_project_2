package agi_p2_server;

public class MainServer {
	
	public static void main(String[] args)
	{
		GameState gs = new GameState();
		
		gs.airplanes.add(new Airplane(1, 2, 3, 4, "hello"));
		gs.airplanes.add(new Airplane(5, 6.6, 7.7, 8.8, "world"));
		gs.bullets.add(new Bullet(1, gs.airplanes.get(0)));
		gs.bullets.add(new Bullet(5, gs.airplanes.get(0)));
		
		RenderClient rc = new RenderClient();
		
		rc.send(gs);
		rc.send(gs);
	}

}
