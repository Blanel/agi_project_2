#include "VertexBufferGL.h"

namespace revel
{
namespace renderer
{
namespace gl
{

VertexBufferGL::VertexBufferGL(BufferHint hint, u32 size)
    : VertexBuffer(hint, size)
{
    ::glGenBuffers(1, &m_Identifier);
}

VertexBufferGL::~VertexBufferGL()
{
	::glDeleteBuffers(1, &m_Identifier);
}

} // ::revel::renderer::gl
} // ::revel::renderer
} // ::revel
