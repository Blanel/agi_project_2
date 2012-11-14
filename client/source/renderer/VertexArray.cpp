#include "VertexArray.h"


namespace revel
{
namespace renderer
{

VertexArray::VertexArray()
    : m_Attributes()
    , m_AttribMap()
    , m_pIndexBuffer(nullptr)
    , m_IndexCount(0)
{
}

VertexArray::~VertexArray()
{
}

bool
VertexArray::has_index_buffer() const
{
    if (m_pIndexBuffer != nullptr)
        return true;
    else
        return false;
}

u32
VertexArray::index_count() const
{
    return m_IndexCount;
    /*

    if (m_pIndexBuffer != nullptr)
        return m_pIndexBuffer->count();
    else
        return 0;
    */
}

VertexBufferAttrib*
VertexArray::attrib(const std::string& name)
{
    auto it = m_AttribMap.find(name);

    if (it != m_AttribMap.end())
        return it->second;
    else
        return nullptr;
}



}

}
