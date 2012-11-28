#ifndef TERRAINMANAGER_H_
#define TERRAINMANAGER_H_
#include <map>

#include "Types.h"
#include "math/Vector2.h"
#include "TerrainTile.h"
#include "renderer/RenderContext.h"
#include "renderer/VertexArray.h"


namespace revel
{
	class TerrainManager
	{
		std::shared_ptr<renderer::RenderContext> m_Context;

		int m_OptimalChunks;
		int m_MinChunks;
		std::map<std::pair<i32,i32>, std::shared_ptr<TerrainTile>> m_Tiles;
		int m_ChunkRes;
		float m_ChunkLen;
		float m_ChunkHei;
		
		

	public:
		TerrainManager(const std::shared_ptr<renderer::RenderContext>& ctx, int optimalChunks, int minChunks, int chunkRes, float chunkLen, float chunkHei);
		~TerrainManager();
		void prune();
		void generate();
		
		std::shared_ptr<renderer::VertexArray> get_chunk(int x, int y);
	};
}
#endif