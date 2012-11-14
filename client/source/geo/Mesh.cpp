#include "Mesh.h"

#include <stdexcept>

using namespace revel::renderer;

namespace revel
{
namespace geo
{

Mesh::Mesh()
    : m_PrimitiveType(PrimitiveType::TRIANGLES)
    , m_WindingOrder(WindingOrder::COUNTER_CLOCKWISE)
{
}

void
Mesh::add_vertex_attrib(const VertexAttributePtr& va)
{
    m_Attributes.push_back(va);
}

void
Mesh::set_index_array(const IndicesPtr &indices)
{
    m_pIndices = indices;
}

const IndicesPtr&
Mesh::index_array()
{
    return m_pIndices;
}

PrimitiveType
Mesh::primitive_type() const
{
    return m_PrimitiveType;
}

void
Mesh::set_primitive_type(PrimitiveType primtype)
{
    m_PrimitiveType = primtype;
}

WindingOrder
Mesh::winding_order() const
{
    return m_WindingOrder;
}

void
Mesh::set_winding_order(WindingOrder order)
{
    m_WindingOrder = order;
}

const std::vector<VertexAttributePtr>&
Mesh::vertex_attrib_array() const
{
    return m_Attributes;
}

}
}
