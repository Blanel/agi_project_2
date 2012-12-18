#include "TerrainTile.h"
#include "SimplexNoise.h"
#include "geo/Mesh.h"
// #include "Image2D.h"

namespace revel
{

TerrainTile::TerrainTile()
{


}

TerrainTile::~TerrainTile()
{}

void 
TerrainTile::set_vertex_array(const std::shared_ptr<renderer::VertexArray>& va)
{
	m_VertexArray = va;
}

const std::shared_ptr<renderer::VertexArray>& 
TerrainTile::vertex_array()
{
	return m_VertexArray;
}

void 
TerrainTile::set_shader_program(const std::shared_ptr<renderer::ShaderProgram>& sp)
{
	m_ShaderProgram = sp;
}

const std::shared_ptr<renderer::ShaderProgram>& 
TerrainTile::shader_program()
{
	return m_ShaderProgram;
}

}