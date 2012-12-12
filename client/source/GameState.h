#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "Types.h"
#include <vector>
#include <string>
#include "renderer/ShaderProgram.h"
#include "renderer/VertexArray.h"
#include "renderer/RenderContext.h"
#include "Camera.h"

namespace revel
{
	class AirPlane
	{
	public:
		f32 x; 
		f32 y;
		f32 angle;
		std::string name;
		bool alive;

		AirPlane();
		~AirPlane();
		
		void set(f32 xn, f32 yn, f32 anglen, bool aliven)
		{
			x = xn;
			y = yn;
			angle = anglen;
			alive = aliven;
		}

	};

	class Bullet
	{
	public:
		f32 x; 
		f32 y;
		f32 angle;
		bool alive;
		bool hit;

		Bullet();
		~Bullet();
		
		void set(f32 xn, f32 yn, f32 anglen, bool aliven, bool hitn)
		{
			x = xn;
			y = yn;
			angle = anglen;
			alive = aliven;
			hit = hitn;
		}
	};


	class GameState
	{
		std::map<i32, AirPlane> airplanes;
		std::map<i32, Bullet> bullets;
	public:
		GameState();
		~GameState();

		void create_plane(i32 id,f32 x, f32 y, f32 angle)
		{
			AirPlane p;
			p.x = x;
			p.y = y;
			p.angle = angle;
			p.alive = true;

			airplanes.insert(std::pair<i32,AirPlane>(id,p));
		}
		
		void update_plane(i32 id, f32 x, f32 y, f32 angle, bool alive)
		{
			airplanes.find(id)->second.set(x,y,angle,alive);
		}
		
		void create_bullet(i32 id, f32 x, f32 y, f32 angle)
		{
			Bullet b;
			b.x = x;
			b.y = y;
			b.angle = angle;
			b.alive = true;
			b.hit = false;
			
			bullets.insert(std::pair<i32,Bullet>(id,b));
			
		}
		
		void update_bullet(i32 id, f32 x, f32 y, f32 angle, bool alive, bool hit)
		{
			bullets.find(id)->second.set(x,y,angle,alive,hit);
		}
		
		std::map<i32, AirPlane>& get_planes() 
		{ 
			return airplanes; 
		}

		std::map<i32, Bullet>& get_bullets()
		{
			return bullets;
		}

		std::pair<f32,f32> getCentre();
		std::pair<std::pair<f32,f32>,std::pair<f32,f32>> getBoundingBox();
	};


}
#endif