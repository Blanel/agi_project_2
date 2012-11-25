#ifndef VERTEXBUFFERATTRIBGL_H
#define VERTEXBUFFERATTRIBGL_H

#include "renderer/VertexBufferAttrib.h"
#include <GL/glew.h>


namespace revel
{
namespace renderer
{
namespace gl
{

class VertexBufferAttribGL : public VertexBufferAttrib
{
public:
    VertexBufferAttribGL(u32 index, const std::shared_ptr<VertexBuffer>& pBuffer, ComponentDatatype type, u32 numOfComponents);
    ~VertexBufferAttribGL();

    void enable_array(bool enable = true);


};

} // ::revel::renderer::gl
} // ::revel::renderer
} // ::revel

#endif // VERTEXBUFFERATTRIBGL_H
