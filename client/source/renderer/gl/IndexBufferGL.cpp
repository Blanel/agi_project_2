#include "IndexBufferGL.h"

namespace revel
{
namespace renderer
{
namespace gl
{

IndexBufferGL::IndexBufferGL(BufferHint hint, u32 size)
    : IndexBuffer(hint, size)
{
    ::glGenBuffers(1, &m_Identifier);
}

IndexBufferGL::~IndexBufferGL()
{
    ::glDeleteBuffers(1, &m_Identifier);
}

} // ::revel::renderer::gl
} // ::revel::renderer
} // ::revel
