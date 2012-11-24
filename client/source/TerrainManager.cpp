#include "TerrainManager.h"
#include <iostream>
#include "Types.h"

namespace revel
{
	TerrainManager::TerrainManager(int optimalChunks, int chunkRes, int chunkLen)
	{
		TerrainManager::optimalChunks = optimalChunks;
		TerrainManager::chunkLen = chunkLen;
		TerrainManager::chunkRes = chunkRes;
	}

	TerrainManager::~TerrainManager()
	{

	}

	void TerrainManager::generate()
	{
		if(TerrainManager::tiles.size() == 0)
		{
			//GetSpawn from server
			//Generate chunks around spawn
		}
		else
		{
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