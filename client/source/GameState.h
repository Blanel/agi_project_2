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

	};

	class Bullet
	{
	public:
		f32 x; 
		f32 y;
		f32 angle;
		bool hit;

		Bullet();
		~Bullet();
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
		
		void update_plane(i32 id, f32 x, f32 y, f32 angle)
		{
		
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