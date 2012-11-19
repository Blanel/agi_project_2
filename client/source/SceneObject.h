#include "renderer/VertexArray.h"

namespace revel
{
namespace renderer
{
	
class SceneObject
{
	std::shared_ptr<VertexArray> m_pVertexArray;


public:
	SceneObject();
	virtual ~SceneObject();

	const std::shared_ptr<VertexArray>& vertex_array();
	
};

}
}