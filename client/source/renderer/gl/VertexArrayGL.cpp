#include "VertexArrayGL.h"

#include <GL/glew.h>

#include "Device.h"

namespace revel
{
namespace renderer
{
namespace gl
{


VertexArrayGL::VertexArrayGL()
{
    ::glGenVertexArrays(1, &m_Identifier);
}

VertexArrayGL::~VertexArrayGL()
{
    ::glDeleteVertexArrays(1, &m_Identifier);
}

void
VertexArrayGL::bind()
{
    ::glBindVertexArray(m_Identifier);
}

void
VertexArrayGL::unbind()
{
    ::glBindVertexArray(0);
}

void
VertexArrayGL::set_index_buffer(const std::shared_ptr<IndexBuffer> &buffer)
{
    this->bind();
    buffer->bind();    
    this->unbind();
}

}
}
}

