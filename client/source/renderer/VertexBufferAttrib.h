#ifndef VERTEXBUFFERATTRIB_H
#define VERTEXBUFFERATTRIB_H

#include "renderer/VertexBuffer.h"
#include "renderer/VertexComponent.h"
#include <memory>

namespace revel
{
namespace renderer
{

class VertexBufferAttrib
{
    std::shared_ptr<VertexBuffer> m_pBuffer;
    ComponentDatatype m_ComponentType;
    u32 m_NumOfComponents;
    bool m_Normalize;
    u32 m_OffsetInBytes;
    u32 m_StrideInBytes;

public:
    VertexBufferAttrib(const std::shared_ptr<VertexBuffer>& pBuffer, ComponentDatatype type, u32 numOfComponents)
        : m_pBuffer(pBuffer)
        , m_ComponentType(type)
        , m_NumOfComponents(numOfComponents)
    {

    }

    virtual ~VertexBufferAttrib() {}

    virtual void enable_array(bool enable = true) = 0;
};

} // ::revel::renderer
} // ::revel

#endif // VERTEXBUFFERATTRIB_H
