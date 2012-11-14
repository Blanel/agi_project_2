#ifndef INDEXBUFFERGL_H
#define INDEXBUFFERGL_H

#include "renderer/IndexBuffer.h"
#include <GL/glew.h>

namespace revel
{
namespace renderer
{
namespace gl
{

class IndexBufferGL
    : public IndexBuffer
{
public:
    IndexBufferGL(BufferHint hint, u32 size = 0);
    ~IndexBufferGL();

    void bind()
    {
        ::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Identifier);
    }

    void unbind()
    {
        ::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void copy_raw_from_sys_mem(void* pSource, u32 offsetInByte, u32 lengthInByte)
    {
        this->bind();

        ::glBufferData(GL_ELEMENT_ARRAY_BUFFER, lengthInByte, pSource, GL_STATIC_DRAW);


        //void* pSourceAddr = pSource + offsetInByte;
        this->unbind();
    }
};

} // ::revel::renderer::gl
} // ::revel::renderer
} // ::revel

#endif // INDEXBUFFERGL_H
