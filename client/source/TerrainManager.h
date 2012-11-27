#ifndef TERRAINMANAGER_H_
#define TERRAINMANAGER_H_
#include <map>

#include "Types.h"
#include "math/Vector2.h"
#include "TerrainTile.h"
#include "renderer/RenderContext.h"



namespace revel
{
	class TerrainManager
	{
		int optimalChunks;
		int minChunks;
		std::map<vec2_i32, std::shared_ptr<TerrainTile>> tiles;
		int chunkRes;
		float chunkLen;
		float chunkHei;
		std::shared_ptr<renderer::RenderContext> ctx;
		

	public:
		TerrainManager(std::shared_ptr<renderer::RenderContext> ctx, int optimalChunks, int minChunks, int chunkRes, float chunkLen, float chunkHei);
		~TerrainManager();
		void prune();
		void generate();
		
		std::shared_ptr<renderer::VertexArray> TerrainManager::get_chunk(int x, int y);
	};
}
#endif