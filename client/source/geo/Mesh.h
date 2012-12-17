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

    static std::shared_ptr<Mesh> create_cube();

    static std::shared_ptr<Mesh> create_quad();

    static std::shared_ptr<Mesh> create_arrow();

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
