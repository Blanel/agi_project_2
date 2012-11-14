#ifndef VERTEXBUFFERGL_H
#define VERTEXBUFFERGL_H

#include "renderer/VertexBuffer.h"

namespace revel
{
namespace renderer
{
namespace gl
{

class VertexBufferGL : public VertexBuffer
{
public:
    VertexBufferGL(BufferHint hint, u32 size = 0);
    ~VertexBufferGL();

    void bind()
    {
        ::glBindBuffer(GL_ARRAY_BUFFER, m_Identifier);
    }

    void unbind()
    {
        ::glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    GLvoid* map_buffer()
    {

    }

    void copy_raw_from_sys_mem(void* pSource, u32 offsetInByte, u32 lengthInByte)
    {
        this->bind();
        ::glBufferData(GL_ARRAY_BUFFER, lengthInByte, pSource, GL_STATIC_DRAW);
        this->unbind();
    }

    template <typename T>
    void copy_from_sys_mem(const std::vector<T>& v)
    {
        copy_raw_from_sys_mem(static_cast<void*>(&v[0]), 0, sizeof(T)*v.size());
    }

    template <typename T>
    void copy_from_sys_mem(const std::vector<T>& v, u32 numOfElems)
    {
        copy_raw_from_sys_mem(static_cast<void*>(&v[0]), 0, sizeof(T)*numOfElems);
    }

    template <typename T>
    void copy_from_sys_mem(const std::vector<T>& v, u32 startElem, u32 numOfElems)
    {
        copy_raw_from_sys_mem(static_cast<void*>(&v[0]), sizeof(T)*startElem, sizeof(T)*numOfElems);
    }

    template <typename T>
    void copy_from_sys_mem(T* pSource, u32 numOfElems)
    {
        copy_raw_from_sys_mem(pSource, 0, numOfElems);
    }

    template <typename T>
    void copy_from_sys_mem(T* pSource, u32 startElem, u32 numOfElems)
    {
        copy_raw_from_sys_mem(static_cast<void*>(pSource), sizeof(T)*startElem, sizeof(T)*numOfElems);
    }




};

} // ::revel::renderer::gl
} // ::revel::renderer
} // ::revel

#endif // VERTEXBUFFERGL_H
