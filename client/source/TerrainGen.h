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
#include "GameState.h"
#include "TerrainTile.h"

namespace revel
{

class Terrain
{
	std::shared_ptr<renderer::RenderContext> m_pCtx;
	std::map<ivec2, std::shared_ptr<TerrainTile>> m_Tiles;
	std::shared_ptr<renderer::ShaderProgram> m_pShaderProgram;
	std::unique_ptr<SimplexNoise> m_pNoiseGen;

	bool m_DrawNormals;

	vec2_i32 m_TileSize;

	// void create_tile(const vec2_i32& p);
	void create_tile(i32 x, i32 y);

public:
	Terrain(const std::shared_ptr<renderer::RenderContext>& ctx, i32 w = 128, i32 h = 128);
	~Terrain();

	void update(const GameState& gs);
	
	const std::shared_ptr<TerrainTile>&	tile(i32 x, i32 y);
	const std::shared_ptr<TerrainTile>&	tile(const vec2_i32& p);

	void draw(const std::shared_ptr<renderer::RenderContext>& ctx, const std::shared_ptr<Camera>& cam);

};


}

#endif // TERRAINGEN_H_
