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

namespace revel
{

class TerrainTile
{
	std::shared_ptr<renderer::VertexArray> m_pVertexArray;

public:
	TerrainTile();

	void set_vertex_array(const std::shared_ptr<renderer::VertexArray>& va);

	const std::shared_ptr<renderer::VertexArray>& vertex_array();
};

class Terrain
{
	std::shared_ptr<renderer::RenderContext> m_pCtx;
	std::map<vec2_i32, std::unique_ptr<TerrainTile>> m_Tiles;
	std::shared_ptr<renderer::ShaderProgram> m_pShaderProgram;
	std::unique_ptr<SimplexNoise> m_pNoiseGen;

	bool m_DrawNormals;

	vec2_i32 m_TileSize;

	void create_tile(const vec2_i32& p);
	void create_tile(i32 x, i32 y);

public:
	Terrain(const std::shared_ptr<renderer::RenderContext>& ctx, i32 w = 128, i32 h = 128);
	~Terrain();

	void update(const GameState& gs);
	
	const std::unique_ptr<TerrainTile>&	tile(const vec2_i32& p);

	void draw(const std::shared_ptr<renderer::RenderContext>& ctx, const std::shared_ptr<Camera>& cam);

};


}

#endif // TERRAINGEN_H_
