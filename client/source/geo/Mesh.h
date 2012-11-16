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
        auto indices = mesh->create_indices<u32>();

        pos->data().push_back(point3(-1, -1,  1));
        pos->data().push_back(point3( 1, -1,  1));
        pos->data().push_back(point3( 1,  1,  1));
        pos->data().push_back(point3(-1,  1,  1));

        pos->data().push_back(point3(-1, -1, -1));
        pos->data().push_back(point3( 1, -1, -1));
        pos->data().push_back(point3( 1,  1, -1));
        pos->data().push_back(point3(-1,  1, -1));

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
        mesh->set_index_array(indices);
        
        return mesh;
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

    //TODO: Does this leak memory? i.e. a new shared_ptr looking at the same object?
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
        if (m_pIndices)
            return std::static_pointer_cast<Indices<T>>(m_pIndices);
        else
            return nullptr;
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
