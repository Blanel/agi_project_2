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
    , m_Attributes()
    , m_pIndices(std::make_shared<Indices<u32>>())
{
}

void
Mesh::add_vertex_attrib(const VertexAttribPtr& va)
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

const std::vector<VertexAttribPtr>&
Mesh::vertex_attrib_array() const
{
    return m_Attributes;
}

std::shared_ptr<Mesh> 
Mesh::create_cube()
{        
    auto mesh = std::make_shared<Mesh>();        
    auto pos = mesh->create_vertex_attrib<point3>("position", 8);

    pos->data().push_back(point3(-1, -1,  1));
    pos->data().push_back(point3( 1, -1,  1));
    pos->data().push_back(point3( 1,  1,  1));
    pos->data().push_back(point3(-1,  1,  1));

    pos->data().push_back(point3(-1, -1, -1));
    pos->data().push_back(point3( 1, -1, -1));
    pos->data().push_back(point3( 1,  1, -1));
    pos->data().push_back(point3(-1,  1, -1));

    auto indices = mesh->indices<u32>();

    indices->add_triangle(0, 1, 2); //front
    indices->add_triangle(2, 3, 0);
    indices->add_triangle(1, 5, 6); //right
    indices->add_triangle(6, 2, 1);
    indices->add_triangle(4, 0, 3); //left
    indices->add_triangle(3, 7, 4);
    indices->add_triangle(4, 5, 6); //back
    indices->add_triangle(6, 7, 4);
    indices->add_triangle(3, 2, 6); //top
    indices->add_triangle(6, 7, 3);
    indices->add_triangle(4, 5, 1); //bottom
    indices->add_triangle(1, 0, 4);

    mesh->add_vertex_attrib(pos);
    
    return mesh;
}

std::shared_ptr<Mesh> 
Mesh::create_quad()
{
    auto quad = std::make_shared<Mesh>();

    auto quadp = quad->create_vertex_attrib<point3>("position");
    auto quadt = quad->create_vertex_attrib<vec2>("texcoord");
    auto quadn = quad->create_vertex_attrib<vec3>("normal");
    

    quadp->data().push_back(point3(-0.5, -0.5, 0));
    quadp->data().push_back(point3( 0.5, -0.5, 0));
    quadp->data().push_back(point3( 0.5,  0.5, 0));
    quadp->data().push_back(point3(-0.5,  0.5, 0));

    quadt->data().push_back(vec2(0.0f, 0.0f));
    quadt->data().push_back(vec2(1.0f, 0.0f));
    quadt->data().push_back(vec2(1.0f, 1.0f));
    quadt->data().push_back(vec2(0.0f, 1.0f));

    quadn->data().push_back(vec3(0, 0, 1));
    quadn->data().push_back(vec3(0, 0, 1));
    quadn->data().push_back(vec3(0, 0, 1));
    quadn->data().push_back(vec3(0, 0, 1));

    auto quadi = quad->indices<u32>();
    quadi->data().push_back(0);
    quadi->data().push_back(1);
    quadi->data().push_back(2);

    quadi->data().push_back(0);
    quadi->data().push_back(2);
    quadi->data().push_back(3);

    return quad;
}

std::shared_ptr<Mesh> 
Mesh::create_arrow()
{
    auto arrow = std::make_shared<Mesh>();
    auto arrowp = arrow->create_vertex_attrib<point3>("position");
    
    arrowp->data().push_back(point3(-0.5, 0, 0.5));
    arrowp->data().push_back(point3( 0.5, 0, 0.5));
    arrowp->data().push_back(point3( 0,  0, -0.5));

    arrowp->data().push_back(point3( 0, 0.5, 0.5));
    arrowp->data().push_back(point3( 0, -0.5, 0.5));
    arrowp->data().push_back(point3( 0, 0, -0.5));


    auto arrowi = arrow->indices<u32>();
    arrowi->data().push_back(0);
    arrowi->data().push_back(1);
    arrowi->data().push_back(2);

    arrowi->data().push_back(0);
    arrowi->data().push_back(2);
    arrowi->data().push_back(3);

    return arrow;        
}

}
}
