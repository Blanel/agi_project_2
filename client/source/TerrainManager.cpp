#include "TerrainManager.h"
#include <iostream>
#include "Types.h"

namespace revel
{
	TerrainManager::TerrainManager(const std::shared_ptr<revel::renderer::RenderContext>& ctx, int optimalChunks, int minChunks, int chunkRes, float chunkLen, float chunkHei)
		: m_Context(ctx)
		, m_OptimalChunks(optimalChunks)
		, m_MinChunks(minChunks)
		, m_ChunkRes(chunkRes)
		, m_ChunkLen(chunkLen)
		, m_ChunkHei(chunkHei)
	{}

	TerrainManager::~TerrainManager()
	{

	}

	void TerrainManager::generate()
	{
		//TerrainTile* test;
		//tiles.insert(std::make_pair(vec2_i32(0,0), test));
		
		if(m_Tiles.size() == 0)
		{
			m_Tiles.insert(std::make_pair(vec2_i32(0,0), std::make_shared<TerrainTile>(m_Context,0,0,m_ChunkRes,m_ChunkLen,m_ChunkHei)));
			//GetSpawn from server
			//Generate chunks around spawn
		}
		else
		{
			std::cout<<"Derp";
			//Loop through all player positions
			//	For each player, check so adjacent chunks have been generated.
			//		If false, generate new chunk and add to list.
		}
		

	}

	std::shared_ptr<renderer::VertexArray> TerrainManager::get_chunk(int x, int y)
	{	
		auto it = m_Tiles.find(vec2_i32(x,y));

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