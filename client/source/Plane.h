#ifndef PLANE_H_
#define PLANE_H_

#include "math/Vector3.h"
#include "math/Point3.h"
#include "math/Transform.h"
#include "renderer/RenderContext.h"
#include "renderer/ShaderProgram.h"
#include "renderer/Texture2D.h"
#include "Camera.h"

namespace revel
{


class Plane
{
	std::shared_ptr<renderer::VertexArray>		m_pVertexArray;
	std::shared_ptr<renderer::ShaderProgram> 	m_pGpuProgram;
	std::shared_ptr<renderer::Texture2D>		m_DiffuseMap;
	
	point3 			m_Position;
	//math::quat 	m_Orientation;

	f32 m_Angle;

	u32 texid;

public:
	Plane(const std::shared_ptr<renderer::VertexArray>& va, 
		  const std::shared_ptr<renderer::ShaderProgram>& sp,
		  f32 x, f32 y,
		  f32 angle = 0)
		: m_pVertexArray(va)
		, m_pGpuProgram(sp)
		, m_Position(point3(x, y, 90))
		, m_Angle(angle)
	{
		Image2D<pixel::RGB_u8> img("e:/test.tga");

		m_DiffuseMap = Device::graphics()->create_texture_2d();
		m_DiffuseMap->copy_from_sys_mem(img);	 
	}

	virtual ~Plane()
	{
		//::glDeleteTextures(1, &texid);		
	}

	void draw(const std::shared_ptr<renderer::RenderContext>& ctx, const std::shared_ptr<Camera>& cam)
	{
		m_pVertexArray->bind();
		m_pGpuProgram->use();

		math::mat4 model = Transform::translate(m_Position.x, m_Position.y, m_Position.z) * Transform::rotate_y(0);
		math::mat4 view = cam->view_matrix();
		math::mat4 projection = cam->projection_matrix();

		//auto& mv = m_pGpuProgram->uniform<mat4>("r_ModelView");
		//auto& p = m_pGpuProgram->uniform<mat4>("r_Projection");
		auto& mvp = m_pGpuProgram->uniform<mat4>("r_MVP");
		auto& diffmap = m_pGpuProgram->uniform<i32>("diffuseMap");
		diffmap = 0;

		m_DiffuseMap->bind();

		mvp = projection * view * model;

		::glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		m_pVertexArray->unbind();
	}

	void update()
	{

	}
};

	
}

#endif // PLANE_H_