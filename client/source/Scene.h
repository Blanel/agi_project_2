#include <memory>
#include "renderer/SceneState.h"
#include "renderer/VertexArray.h"
#include "renderer/RenderContext.h"
#include "renderer/ShaderProgram.h"
#include "geo/Mesh.h"


namespace revel
{

class RenderItem
{
	std::shared_ptr<renderer::VertexArray> m_pVertexArray;


};

class SceneNode
{
	SceneNode* m_pParent;
	std::vector<std::unique_ptr<SceneNode>> m_pChildren;

public:
	SceneNode(SceneNode* parent = nullptr)
		: m_pParent(parent)
	{}
	
	~SceneNode()
	{}


	SceneNode* parent() { return m_pParent; }

/*
	void add_child(const SceneNode& node) 
	{ 
		if (std::find(m_pChildren.begin(), m_pChildren.end(), &node) == *(m_pChildren.end()->get())
			m_pChildren.push_back(std::move(node));
	}
	*/

};

class GeoNode : public SceneNode
{
	point3 m_Position;
	math::quat m_Orientation;

	std::shared_ptr<renderer::VertexArray> m_pVertexArray;
public:
	GeoNode(const std::shared_ptr<geo::Mesh>& m, const point3& p = point3::Origin, const math::quat& o = math::quat::Identity)
		: m_Position(p)
		, m_Orientation(o)
		, m_pVertexArray(nullptr)
	{

	}

	virtual ~GeoNode() 
	{}
	
	void set_vertex_array(const std::shared_ptr<renderer::VertexArray>& va)
	{
		m_pVertexArray = va;
	}

	const std::shared_ptr<renderer::VertexArray>& vertex_array()
	{
		return m_pVertexArray;
	}

};

class TerrainNode : public SceneNode
{
	std::shared_ptr<renderer::ShaderProgram> m_pShader;

public:
	TerrainNode()
	{
		m_pShader = Device::graphics()->create_shader_program_from_file("terrain_vs.glsl", 
    															  		"terrain_fs.glsl"); 


	}

	void draw()
	{
		m_pShader->use();
		//m_pVertexArray->bind();
		//::glDrawElements(GL_TRIANGLES, )


	}


};

class Scene
{
	std::shared_ptr<renderer::RenderContext> 	m_pContext; // Keep this global instead?

	std::shared_ptr<renderer::SceneState> 		m_pSceneState;
	std::shared_ptr<Camera>						m_pActiveCamera;

	std::unique_ptr<SceneNode>					m_pRoot;
	
public:
	Scene(const std::shared_ptr<renderer::RenderContext>& ctx);
	virtual ~Scene();

	void set_camera(const std::shared_ptr<Camera>& cam) { m_pActiveCamera = cam; }


	const std::shared_ptr<Camera>& camera() { return m_pActiveCamera; }
	const std::unique_ptr<SceneNode>& root() { return m_pRoot; }
};
	
}