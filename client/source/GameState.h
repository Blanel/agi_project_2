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
		f32 m_x; 
		f32 m_y;
		f32 m_angle;
		bool m_alive;

		AirPlane();
		AirPlane(f32 x, f32 y, f32 angle, bool alive)
		{
			m_x = x;
			m_y = y;
			m_angle = angle;
			m_alive = alive;
		}
		~AirPlane();
		
		void set(f32 x, f32 y, f32 angle, bool alive)
		{
			m_x = x;
			m_y = y;
			m_angle = angle;
			m_alive = alive;
		}

	};

	class Bullet
	{
	public:
		f32 m_x; 
		f32 m_y;
		f32 m_angle;
		bool m_alive;
		bool m_hit;

		Bullet();
		Bullet(f32 x, f32 y, f32 angle, bool alive, bool hit)
		{
			m_x = x;
			m_y = y;
			m_angle = angle;
			m_alive = alive;
			m_hit = hit;
		}
		~Bullet();
		
		void set(f32 x, f32 y, f32 angle, bool alive, bool hit)
		{
			m_x = x;
			m_y = y;
			m_angle = angle;
			m_alive = alive;
			m_hit = hit;
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
			airplanes[id]=AirPlane(x,y,angle,true);
		}
		
		void update_plane(i32 id, f32 x, f32 y, f32 angle, bool alive)
		{
			airplanes[id]=AirPlane(x,y,angle,alive);
		}
		
		void create_bullet(i32 id, f32 x, f32 y, f32 angle)
		{
			bullets[id]=Bullet(x,y,angle,true,false);
			
		}
		
		void update_bullet(i32 id, f32 x, f32 y, f32 angle, bool alive, bool hit)
		{
			bullets[id]=Bullet(x,y,angle,alive,hit);
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