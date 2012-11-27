#include "TerrainManager.h"
#include <iostream>
#include "Types.h"

namespace revel
{
	TerrainManager::TerrainManager(std::shared_ptr<revel::renderer::RenderContext> ctx, int optimalChunks, int minChunks, int chunkRes, float chunkLen, float chunkHei)
	{
		TerrainManager::optimalChunks = optimalChunks;
		TerrainManager::chunkLen = chunkLen;
		TerrainManager::chunkRes = chunkRes;
		TerrainManager::minChunks = minChunks;
		TerrainManager::ctx = ctx;
		TerrainManager::chunkHei = chunkHei;
	}

	TerrainManager::~TerrainManager()
	{

	}

	void TerrainManager::generate()
	{
		//TerrainTile* test;
		//tiles.insert(std::make_pair(vec2_i32(0,0), test));
		if(tiles.size() == 0)
		{
			tiles.insert(std::make_pair(vec2_i32(0,0), std::make_shared<TerrainTile>(TerrainTile(ctx,0,0,chunkRes,chunkLen,chunkHei))));
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
		std::map<vec2_i32, std::shared_ptr<TerrainTile>>::iterator it;
		it = tiles.find(vec2_i32(x,y));
		if(it != tiles.end())
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