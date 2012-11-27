#ifndef TERRAINTILE_H_
#define TERRAINTILE_H_

#include "renderer/VertexArray.h"
#include "renderer/RenderContext.h"

namespace revel
{

class TerrainTile
{
	
public:
	TerrainTile(std::shared_ptr<renderer::RenderContext> ctx, float x, float y, int res, float len, float hei);
	~TerrainTile();
	std::shared_ptr<renderer::VertexArray> va;
};

}

#endif