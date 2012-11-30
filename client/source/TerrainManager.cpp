#include "TerrainManager.h"
#include <iostream>
#include "Types.h"
#include "math/RMath.h"
#include "math/Transform.h"
#include "renderer/Uniform.h"
#include "Image2D.h"

namespace revel
{
	TerrainManager::TerrainManager(const std::shared_ptr<revel::renderer::RenderContext>& ctx, int optimalChunks, int radiusChunks, int chunkRes, float chunkLen, float chunkHei)
		: m_Context(ctx)
		, m_OptimalChunks(optimalChunks)
		, m_RadiusChunks(radiusChunks)
		, m_ChunkRes(chunkRes)
		, m_ChunkLen(chunkLen)
		, m_ChunkHei(chunkHei)
	{

	    m_pShaderProgram = Device::graphics()->create_shader_program_from_file("../client/source/shaders/terrain.vs", 
    															  			   "../client/source/shaders/terrain.fs"); 

	    Image2D<pixel::RGB_u8> diffuse("e:/ground.tga");

	    m_pDiffuseMap = Device::graphics()->create_texture_2d();
	    m_pDiffuseMap->copy_from_sys_mem(diffuse);
	}

	TerrainManager::~TerrainManager()
	{

	}

	void TerrainManager::generate(GameState gs)
	{
		std::pair<f32,f32> centre = gs.getCentre();
		for(i32 i= math::ffloor(centre.first/m_ChunkRes)-m_RadiusChunks ; i< math::ffloor(centre.first/m_ChunkRes)+m_RadiusChunks ; i++)
		{
			for(i32 j= math::ffloor(centre.second/m_ChunkRes)-m_RadiusChunks ; j< math::ffloor(centre.second/m_ChunkRes)+m_RadiusChunks ; j++)
			{
				auto it = m_Tiles.find(std::make_pair(i,j));
				if(it == m_Tiles.end())
				{
					m_Tiles.insert(std::make_pair(std::make_pair(i,j), std::make_shared<TerrainTile>(TerrainTile(m_Context, i*m_ChunkLen,j*m_ChunkLen, m_ChunkRes, m_ChunkLen, m_ChunkHei))));
					R_LOG_INFO("NEW CHUNK: "<<i<<" "<<j);
				}					
			}
		}
	}

	std::shared_ptr<renderer::VertexArray> TerrainManager::get_chunk(int x, int y)
	{	
		auto it = m_Tiles.find(std::make_pair(x,y));

		if(it != m_Tiles.end())
			return it->second->va;
		else
			return false;
	}

	void TerrainManager::prune()
	{
		/*
			Loop through player positions
				For each player mark all adjacent chunks
			For each unmarked chunk
				Order by max -> min distance to player
			While optimal ammount of chunks < Generated chunks
				Remove furthest chunk.
		*/
	}

	void TerrainManager::draw(const std::shared_ptr<Camera>& cam)
	{
		::glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		//::glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );


		m_pShaderProgram->use();		
		m_pDiffuseMap->bind();

		
		auto& mvp = m_pShaderProgram->uniform<math::mat4>("r_MVP");
		//auto& mv= m_pShaderProgram->uniform<math::mat4>("r_ModelView");

		/*
		auto& lp = m_pShaderProgram->uniform<vec4>("LightPosition");
		auto& li = m_pShaderProgram->uniform<vec4>("LightIntensity");

		auto& kd = m_pShaderProgram->uniform<vec3>("Kd");
		auto& ka = m_pShaderProgram->uniform<vec3>("Ka");
		auto& ks = m_pShaderProgram->uniform<vec3>("Ks");
		auto& s = m_pShaderProgram->uniform<f32>("Shininess");

		lp = vec4(0.8, 0.2, 0, 1);
		li = vec4(1, 1, 1, 1);

		ka = vec3(0.3, 0.5, 0.4);
		kd = vec3(0.3, 0.5, 0.4);
		ks = vec3(0.8, 0.8, 0.8);
		s = 80.0f;
		*/


/*
		auto& lightAmbient = m_pShaderProgram->uniform<vec4>("lightAmbient");
		auto& lightDiffuse = m_pShaderProgram->uniform<vec4>("lightDiffuse");
		auto& lightDir     = m_pShaderProgram->uniform<vec3>("lightDirection");


		lightAmbient = vec4(0.05f, 0.05f, 0.05f, 1.0f);
		lightDiffuse = vec4(1.0f, 1.0f, .8f, 1.0f);
		lightDir = vec3(0.7f, 0.3f, 0.0f).normalized();
*/

		auto terrainptr = m_Tiles[std::pair<i32, i32>(0, 0)];

		terrainptr->va->bind();

		mvp = cam->projection_matrix() * cam->view_matrix() * math::Transform::translate(0 * 127, 0 * 127, 0);
		//mv = cam->view_matrix() * math::Transform::translate(0 * 127, 0 * 127, 0);

		::glDrawElements(GL_TRIANGLES, terrainptr->va->index_count(), GL_UNSIGNED_INT, 0);


/*
		for (auto iter = m_Tiles.begin(); iter != m_Tiles.end(); ++iter)
		{
			mvp = cam->projection_matrix() * cam->view_matrix() * math::Transform::translate(iter->first.first * 127, iter->first.second * 127, 0);

			iter->second->va->bind();
			::glDrawElements(GL_TRIANGLES, iter->second->va->index_count(), GL_UNSIGNED_INT, 0);
		}
*/
	}
}