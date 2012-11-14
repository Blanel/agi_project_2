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
	//TODO: DELETE BUFFER!!
	R_LOG_INFO("NOTE: NOT DELETING BUFFER");
}

} // ::revel::renderer::gl
} // ::revel::renderer
} // ::revel
