#ifndef CLOUD_H_
#define CLOUD_H_

#include "renderer/VertexArray.h"
#include "renderer/RenderContext.h"
#include "BoundingVolume.h"
#include "Image2D.h"
#include "Camera.h"
#include "geo/Mesh.h"

#include "pugixml.hpp"

#include "SimplexNoise.h"

#include <string>
#include <sstream>

namespace revel
{


class CubeImage
{
	std::shared_ptr<Image2D<pixel::RGBA_u8>> m_pTop;
	std::shared_ptr<Image2D<pixel::RGBA_u8>> m_pBottom;
	std::shared_ptr<Image2D<pixel::RGBA_u8>> m_pLeft;
	std::shared_ptr<Image2D<pixel::RGBA_u8>> m_pRight;
	std::shared_ptr<Image2D<pixel::RGBA_u8>> m_pFront;
	std::shared_ptr<Image2D<pixel::RGBA_u8>> m_pBack;

public:
	CubeImage(u32 w, u32 h)
	{
		
		m_pTop 		= std::make_shared<Image2D<pixel::RGBA_u8>>(w, h);
		m_pBottom 	= std::make_shared<Image2D<pixel::RGBA_u8>>(w, h);
		m_pLeft 	= std::make_shared<Image2D<pixel::RGBA_u8>>(w, h);
		m_pRight 	= std::make_shared<Image2D<pixel::RGBA_u8>>(w, h);
		m_pFront 	= std::make_shared<Image2D<pixel::RGBA_u8>>(w, h);
		m_pBack 	= std::make_shared<Image2D<pixel::RGBA_u8>>(w, h);
	}

	const std::shared_ptr<Image2D<pixel::RGBA_u8>>& top() { return m_pTop; }
	const std::shared_ptr<Image2D<pixel::RGBA_u8>>& bottom() { return m_pBottom; }
	const std::shared_ptr<Image2D<pixel::RGBA_u8>>& left() { return m_pLeft; }
	const std::shared_ptr<Image2D<pixel::RGBA_u8>>& right() { return m_pRight; }
	const std::shared_ptr<Image2D<pixel::RGBA_u8>>& front() { return m_pFront; }
	const std::shared_ptr<Image2D<pixel::RGBA_u8>>& back() { return m_pBack; }

	static CubeImage generate_fractal_cube()
	{
		CubeImage cube(256, 256);
		SimplexNoise simplex;

		simplex.set_amplitude(1.0f);
		simplex.set_frequency(0.5f);
		simplex.set_octaves(4);
		simplex.set_persistance(1.0f);

		for (u32 y = 0; y < 256; ++y)
		{
			for (u32 x = 0; x < 256; ++x)
			{
				auto n1 = simplex.noise(0, x, y);
				f32 n1n = (n1 + 1.0f) * 128.0f - 1;
				
				auto n2 = simplex.noise(x, y, 255);
				f32 n2n = (n2 + 1.0f) * 128.0f - 1;


				cube.front()->operator()(x,y) = pixel::RGBA_u8(n1n);
			}			
		}

		TGA::write("E:/test123.tga", *(cube.front()));

		return cube;
	}

};


class Cloud
{
	std::shared_ptr<renderer::VertexArray> m_VA;
	BBox m_BoundingBox;
	//TextureCube m_FractalCube;

	std::shared_ptr<ShaderProgram> m_pShaderProgram;

public:
	Cloud()
	{
	    auto cube_sp = Device::graphics()->create_shader_program_from_file("../client/source/shaders/cube.vs", 
			 								  	    				   	   "../client/source/shaders/cube.fs");

	    m_pShaderProgram = cube_sp;
	}

	void load(const std::string& file)
	{
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(file.c_str());

		auto cloud = std::make_shared<geo::Mesh>();

	    auto cloudp = cloud->create_vertex_attrib<point3>("position");
	    auto cloudn = cloud->create_vertex_attrib<vec3>("normal");

		u32 vcount = doc.child("COLLADA").child("library_geometries").child("geometry").child("mesh").child("source").child("float_array").attribute("count").as_uint() / 3;
		auto vtext = doc.child("COLLADA").child("library_geometries").child("geometry").child("mesh").child("source").child("float_array");

		auto vstr = vtext.child_value();
		std::stringstream vss(vstr);

		// u32 vcount = doc.child("COLLADA").child("library_geometries").child("geometry").child("mesh").child("source").child("float_array").attribute("count").as_uint() / 3;
		// auto vtext = doc.child("COLLADA").child("library_geometries").child("geometry").child("mesh").child("source").child("float_array");

		// auto vstr = vtext.child_value();
		// std::stringstream vss(vstr);


		f32 x, y, z;

		for (u32 i = 0; i < vcount; ++i)
		{
			vss >> x;
			vss >> y;
			vss >> z;

			cloudp->data().push_back(point3(x, y, z));
		}

		R_LOG_INFO("Vertices: " << x << ", " << y << ", " << z);

		point3 p(x, y, z);




	}

	void draw(const std::shared_ptr<renderer::RenderContext>& ctx, const std::shared_ptr<Camera>& cam)
	{
		// ::glDisable(GL_DEPTH_TEST);

		m_VA->bind();
		m_pShaderProgram->use();

		math::mat4 model = Transform::translate(0, 0, 200) * Transform::rotate_y(math::PI/4);
		math::mat4 view = cam->view_matrix();
		math::mat4 projection = cam->projection_matrix();

		auto& mvp = m_pShaderProgram->uniform<mat4>("r_MVP");
		auto& mv = m_pShaderProgram->uniform<mat4>("r_ModelView");
		mvp = projection * view * model;
		mv = view * model;

		::glDrawElements(GL_TRIANGLES, m_VA->index_count(), GL_UNSIGNED_INT, 0);

		m_VA->unbind();
	}

	void set_vertex_array(const std::shared_ptr<VertexArray>& va)
	{
		m_VA = va;
	}

	const std::shared_ptr<VertexArray>&
	vertex_array() const
	{
		return m_VA;
	}
};

class CloudLayer
{

	void draw(const std::shared_ptr<renderer::RenderContext>& ctx, const std::shared_ptr<Camera>& cam)
	{
		
	}
};

}

#endif // CLOUD_H_