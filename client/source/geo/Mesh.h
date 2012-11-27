#ifndef R_MESH_H
#define R_MESH_H

#include <vector>
#include <map>
#include <memory>

#include "Log.h"

#include "renderer/PrimitiveType.h"
#include "renderer/WindingOrder.h"
#include "geo/VertexAttribute.h"
#include "renderer/Indices.h"

namespace revel
{
namespace geo
{

class Mesh
{
protected:
    renderer::PrimitiveType         m_PrimitiveType;
    renderer::WindingOrder          m_WindingOrder;

    VertexAttribArray               m_Attributes;
    std::shared_ptr<IndicesBase>    m_pIndices;

public:
    Mesh();

    static std::shared_ptr<Mesh> create_cube()
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

    static std::shared_ptr<Mesh> create_quad()
    {
        auto quad = std::make_shared<Mesh>();

        auto quadp = quad->create_vertex_attrib<point3>("position");
        auto quadn = quad->create_vertex_attrib<vec3>("normal");
        auto quadt = quad->create_vertex_attrib<vec2>("texcoord");

        quadp->data().push_back(point3(-0.5, -0.5, 0));
        quadp->data().push_back(point3( 0.5, -0.5, 0));
        quadp->data().push_back(point3( 0.5,  0.5, 0));
        quadp->data().push_back(point3(-0.5,  0.5, 0));

        quadn->data().push_back(vec3(0, 0, 1));
        quadn->data().push_back(vec3(0, 0, 1));
        quadn->data().push_back(vec3(0, 0, 1));
        quadn->data().push_back(vec3(0, 0, 1));

        quadt->data().push_back(vec2(0, 0));
        quadt->data().push_back(vec2(1, 0));
        quadt->data().push_back(vec2(1, 1));
        quadt->data().push_back(vec2(0, 1));

        auto quadi = quad->indices<u32>();
        quadi->data().push_back(0);
        quadi->data().push_back(1);
        quadi->data().push_back(2);

        quadi->data().push_back(0);
        quadi->data().push_back(2);
        quadi->data().push_back(3);

        return quad;
    }

    template <typename T>
    std::shared_ptr<VertexAttrib<T>> create_vertex_attrib(const std::string& name, u32 capacity = 0)
    {
        auto attrib = std::make_shared<VertexAttrib<T>>(name, capacity);
        m_Attributes.push_back(attrib);

        return attrib;
    }

    template <typename T>
    std::shared_ptr<Indices<T>> create_indices(u32 capacity = 0)
    {
        if (m_pIndices != nullptr)
        {
            R_LOG_ERR("Already contains an index array");
        }
        else
        {
            m_pIndices = std::make_shared<Indices<T>>(capacity);    
        }
        
        return std::static_pointer_cast<Indices<T>>(m_pIndices);
    }

    template <typename T>
    std::shared_ptr<T> create_index(u32 capacity = 0)
    {
        if (m_pIndices != nullptr)
        {
            R_LOG_ERR("Already contains an index array");
        }

        auto indices = std::make_shared<T>(capacity);
        m_pIndices = indices;
        return indices;
    }

    void add_vertex_attrib(const VertexAttribPtr& va);

    const std::vector<VertexAttribPtr>& vertex_attrib_array() const;

    template <typename T>
    std::shared_ptr<VertexAttrib<T>> vertex_attrib(const std::string& name)
    {
        for (auto attrib : m_Attributes)
        {
            if (attrib->name() == name)
                return std::static_pointer_cast<VertexAttrib<T>>(attrib);
        }

        return nullptr;
    }

    template <typename T>
    std::shared_ptr<Indices<T>> indices()
    {
        return std::static_pointer_cast<Indices<T>>(m_pIndices);
    }


    void set_index_array(const IndicesPtr& indices);
    const IndicesPtr& index_array();

    renderer::PrimitiveType primitive_type() const;
    renderer::WindingOrder winding_order() const;

    void set_primitive_type(renderer::PrimitiveType primtype);
    void set_winding_order(renderer::WindingOrder order);   
};

}
}

#endif // MESH_H
