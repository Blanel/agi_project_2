#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "Types.h"
#include <vector>
#include <string>
#include "renderer/ShaderProgram.h"
#include "renderer/VertexArray.h"
#include "renderer/RenderContext.h"
#include "Camera.h"
//#include "math/Transform.h"

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
		
		std::shared_ptr<renderer::VertexArray> 	m_pPlaneVertexArray;
		std::shared_ptr<renderer::ShaderProgram> 	m_pPlaneShaderProgram;
	public:
		GameState();
		~GameState();

		void set_plane_va(const std::shared_ptr<renderer::VertexArray>& va)
		{
			m_pPlaneVertexArray = va;
		}
		
		void set_plane_sp(const std::shared_ptr<renderer::ShaderProgram>& sp)
		{
			m_pPlaneShaderProgram = sp;
		}
		
		void draw(const std::shared_ptr<renderer::RenderContext>& ctx, const std::shared_ptr<Camera>& cam)
		{
			::glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			
			m_pPlaneVertexArray->bind();
			m_pPlaneShaderProgram->use();
		
			auto p = airplanes.begin();
		
			while (p != airplanes.end())
			{
				f32 x, y;
				
				x = p->second.m_x;
				y = p->second.m_y;
				
				math::mat4 model 	  = math::Transform::translate(x, y, 50) * math::Transform::rotate_y(0) * math::Transform::scale(2);
				math::mat4 view 	  = cam->view_matrix();
				math::mat4 projection = cam->projection_matrix();

				auto& color = m_pPlaneShaderProgram->uniform<vec3>("r_Color");
				color = vec3(0.7, 0.6, 0.9);

				auto& mvp = m_pPlaneShaderProgram->uniform<math::mat4>("r_MVP");
				mvp = projection * view * model;

				::glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				p++;
			}
			m_pPlaneVertexArray->unbind();

			
		}
		
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