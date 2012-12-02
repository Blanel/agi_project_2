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
		std::vector<AirPlane> airplanes;
		std::vector<Bullet> bullets;
	public:
		GameState();
		~GameState();

		void create_plane(f32 x, f32 y, f32 angle, const std::string name = "")
		{
			AirPlane p;
			p.x = x;
			p.y = y;
			p.angle = angle;
			p.name = name;
			p.alive = true;

			airplanes.push_back(p);
		}

		std::vector<AirPlane>& get_planes() 
		{ 
			return airplanes; 
		}

		std::vector<Bullet>& get_bullets()
		{
			return bullets;
		}




		std::pair<f32,f32> getCentre();
		std::pair<std::pair<f32,f32>,std::pair<f32,f32>> getBoundingBox();

	};


}
#endif