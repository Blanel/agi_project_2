#ifndef TERRAINTILE_H_
#define TERRAINTILE_H_

#include "renderer/VertexArray.h"
#include "renderer/RenderContext.h"
#include "math/Point3.h"
#include "math/Vector3.h"
#include "Surface.h"

namespace revel
{

struct TerrainVertex
{
	point3 pos;
	vec3 normal;
	vec2 uv;
};

class TerrainTile// : public Surface<TerrainVertex>
{	
	std::shared_ptr<renderer::VertexArray> m_VertexArray;
	std::shared_ptr<renderer::ShaderProgram> m_ShaderProgram;

public:
	TerrainTile();
	~TerrainTile();

	const std::shared_ptr<renderer::VertexArray>& vertex_array();
	void set_vertex_array(const std::shared_ptr<renderer::VertexArray>& va);

	const std::shared_ptr<renderer::ShaderProgram>& shader_program();
	void set_shader_program(const std::shared_ptr<renderer::ShaderProgram>& sp);	

};

}

#endif