#include "TerrainManager.h"
#include <iostream>
#include "Types.h"

namespace revel
{
	TerrainManager::TerrainManager(int optimalChunks, int minChunks, int chunkRes, int chunkLen)
	{
		TerrainManager::optimalChunks = optimalChunks;
		TerrainManager::chunkLen = chunkLen;
		TerrainManager::chunkRes = chunkRes;
		TerrainManager::minChunks = minChunks;
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
			std::cout<<"Herp";
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