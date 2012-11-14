#include "VertexBuffer.h"

namespace revel
{
namespace renderer
{

VertexBuffer::VertexBuffer(BufferHint hint, u32 size)
    : m_Hint(hint)
    , m_SizeInBytes(size)
{
    ::glGenBuffers(1, &m_Identifier);
}

VertexBuffer::~VertexBuffer()
{
    ::glDeleteBuffers(1, &m_Identifier);
}

} // ::revel::renderer
} // ::revel
