#include "TerrainManager.h"
#include <iostream>
#include "Types.h"
#include "math/RMath.h"


namespace revel
{
	TerrainManager::TerrainManager(const std::shared_ptr<revel::renderer::RenderContext>& ctx, int optimalChunks, int radiusChunks, int chunkRes, float chunkLen, float chunkHei)
		: m_Context(ctx)
		, m_OptimalChunks(optimalChunks)
		, m_RadiusChunks(radiusChunks)
		, m_ChunkRes(chunkRes)
		, m_ChunkLen(chunkLen)
		, m_ChunkHei(chunkHei)
	{}

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
					m_Tiles.insert(std::make_pair(std::make_pair(i,j), std::make_shared<TerrainTile>(TerrainTile(m_Context, i,j, m_ChunkRes, m_ChunkLen, m_ChunkHei))));
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
}