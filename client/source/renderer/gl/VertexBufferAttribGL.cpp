#include "VertexBufferAttribGL.h"

#include "Log.h"

namespace revel
{
namespace renderer
{
namespace gl
{

VertexBufferAttribGL::VertexBufferAttribGL(u32 index, const std::shared_ptr<VertexBuffer>& pBuffer, ComponentDatatype type, u32 numOfComponents)
    : VertexBufferAttrib(index, pBuffer, type, numOfComponents)
{
    pBuffer->bind();

    GLint       gl_size = numOfComponents;
    GLenum      gl_type;
    GLboolean   gl_normalized = GL_FALSE;
    GLsizei     gl_stride = 0;

    switch(type)
    {
    case ComponentDatatype::FLOAT32:
        gl_type = GL_FLOAT;
        break;
    default:
        R_LOG_ERR("Unknown datatype");
    }

    ::glVertexAttribPointer(index, gl_size, gl_type, gl_normalized, gl_stride, 0);
    this->enable_array();

    pBuffer->unbind();
}

VertexBufferAttribGL::~VertexBufferAttribGL()
{

}

void
VertexBufferAttribGL::enable_array(bool enable)
{
    enable ? ::glEnableVertexAttribArray(this->index()) : ::glDisableVertexAttribArray(this->index());
}

} // ::revel::renderer::gl
} // ::revel::renderer
} // ::revel
