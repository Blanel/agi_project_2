#ifndef TERRAINGEN_H_
#define TERRAINGEN_H_

#include "Types.h"
#include "math/Vector2.h"
#include <map>
#include <memory>
#include "SimplexNoise.h"
#include "renderer/VertexArray.h"
#include "renderer/RenderContext.h"
#include "renderer/ShaderProgram.h"
#include "Camera.h"


namespace revel
{

class TerrainTile
{
	std::shared_ptr<renderer::VertexArray> m_pVertexArray;

public:
	TerrainTile()
	{

	}

	void set_vertex_array(const std::shared_ptr<renderer::VertexArray>& va)
	{
		m_pVertexArray = va;
	}

	const std::shared_ptr<VertexArray>& vertex_array()
	{
		return  m_pVertexArray;
	}
};

class Terrain
{
	std::shared_ptr<renderer::RenderContext> m_pCtx;
	std::map<vec2_i32, std::unique_ptr<TerrainTile>> m_Tiles;
	std::shared_ptr<renderer::ShaderProgram> m_pShaderProgram;
	std::unique_ptr<SimplexNoise> m_pNoiseGen;

	void
	create_tile(const vec2_i32& p)
	{
		std::unique_ptr<TerrainTile> tile(new TerrainTile());

		auto mesh = std::make_shared<geo::Mesh>();    
	    auto meshp = mesh->create_vertex_attrib<point3>("position");
	    auto meshn = mesh->create_vertex_attrib<vec3>("normals");
	    auto mesht = mesh->create_vertex_attrib<vec2>("uv0");
	    auto meshi = mesh->indices<u32>();

	    Image2D<pixel::Gray_f32> hmap(128, 128);

		for(int y=0; y<128 ; y++)
		{
			for(int x=0 ; x<128 ; x++)
			{
				hmap(x, y).val = m_pNoiseGen->noise(x,y);
				meshp->data().push_back(point3(x,y,m_pNoiseGen->noise(x,y)));
				mesht->data().push_back(vec2(x / (128.0f / 16), y / (128.0f / 16)));
			}
		}

		for(int i = 0 ; i < 128 -1 ; i++)
		{
			for(int j = 0 ; j < 128 -1 ; j++)
			{
				meshi->add_triangle(i*128+j+128, i*128+j+128+1, i*128+j+1);
	    		meshi->add_triangle(i*128+j+1, i*128+j, i*128+j+128);
			}		
		}


		std::vector<vec3> normals(128 * 128, vec3::UnitZ);


		for (i32 y = 1; y < 128 - 1; ++y)
		{
			for (i32 x = 1; x < 128 - 1; ++x)
			{
				//upper left

				vec3 u = point3(x, y+1, hmap(x, y+1).val) - point3(x, y, hmap(x, y).val);
				vec3 l = point3(x-1, y, hmap(x-1, y).val) - point3(x, y, hmap(x, y).val);
				vec3 r = point3(x+1, y, hmap(x+1, y).val) - point3(x, y, hmap(x, y).val);
				vec3 d = point3(x, y-1, hmap(x, y-1).val) - point3(x, y, hmap(x, y).val);

				vec3 uln = math::cross(math::normalize(u), math::normalize(l));
				vec3 urn = math::cross(math::normalize(r), math::normalize(u));
				vec3 lrn = math::cross(math::normalize(d), math::normalize(r));
				vec3 lln = math::cross(math::normalize(l), math::normalize(d));

				math::normalize(uln);
				math::normalize(urn);
				math::normalize(lrn);
				math::normalize(lln);

				normals[y * 128 + x] = (uln + urn + lrn + lln)/4;
			}
		}

		for (auto n : normals)
			meshn->data().push_back(n);

		tile->set_vertex_array(m_pCtx->create_vertex_array(mesh));

		m_Tiles[p] = std::move(tile);
	}

public:
	Terrain(const std::shared_ptr<renderer::RenderContext>& ctx)
	{
		m_pCtx = ctx;

		m_pNoiseGen = std::unique_ptr<SimplexNoise>(new SimplexNoise());
		m_pNoiseGen->set_frequency(4.0f/128.0f);
		m_pNoiseGen->set_octaves(6);
		m_pNoiseGen->set_amplitude(3.0f);
		m_pNoiseGen->set_persistance(0.3f);

		m_pShaderProgram = Device::graphics()->create_shader_program_from_file("../client/source/shaders/terrain.vs",
																			   "../client/source/shaders/terrain.fs");

		create_tile(vec2_i32::Zero);
	}

	~Terrain()
	{

	}

	void update(const GameState& gs)
	{
		//step through all tiles, if tile > set distance, remove from map

	}

	const std::unique_ptr<TerrainTile>&
	tile(const vec2_i32& p)
	{
		return m_Tiles[p];
	}

	void draw(const std::shared_ptr<RenderContext>& ctx, const std::shared_ptr<Camera>& cam)
	{
		//::glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		::glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

		m_pShaderProgram->use();		
		//m_pDiffuseMap->bind();
		
		auto& mvp = m_pShaderProgram->uniform<math::mat4>("r_MVP");
		auto& mv= m_pShaderProgram->uniform<math::mat4>("r_ModelView");

		for (auto iter = m_Tiles.begin(); iter != m_Tiles.end(); ++iter)
		{
			mvp = cam->projection_matrix() * cam->view_matrix() * math::Transform::translate(iter->first.x * 127, iter->first.y * 127, 0);
			// mv = cam->view_matrix() * math::Transform::translate(iter->first.first * 127, iter->first.second * 127, 0);

			auto& va = iter->second->vertex_array();
			va->bind();
			::glDrawElements(GL_TRIANGLES, va->index_count(), GL_UNSIGNED_INT, 0);
		}
	}

};


}

#endif // TERRAINGEN_H_
