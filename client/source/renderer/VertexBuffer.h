#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "Types.h"
#include "renderer/GpuObject.h"
#include "renderer/BufferHint.h"
#include <vector>

namespace revel
{
namespace renderer
{

class VertexBuffer
    : public GpuObject
{
    BufferHint m_Hint;
    u32 m_SizeInBytes;

public:
    VertexBuffer(BufferHint hint, u32 size = 0);
    virtual ~VertexBuffer();

    virtual void bind() = 0;

    virtual void unbind() = 0;

    BufferHint usage_hint()
    {
        return m_Hint;
    }

    u32 size_in_bytes()
    {
        return m_SizeInBytes;
    }

    virtual void copy_raw_from_sys_mem(void* pSource, u32 offsetInByte, u32 lengthInByte) = 0;

    template <typename T>
    void copy_from_sys_mem(const std::vector<T>& v)
    {
        copy_raw_from_sys_mem((void*)(&v[0]), 0, sizeof(T)*v.size());
    }

    template <typename T>
    void copy_from_sys_mem(const std::vector<T>& v, u32 numOfElems)
    {
        copy_raw_from_sys_mem((void*)(&v[0]), 0, sizeof(T)*numOfElems);
    }

    template <typename T>
    void copy_from_sys_mem(const std::vector<T>& v, u32 startElem, u32 numOfElems)
    {
        copy_raw_from_sys_mem((void*)(&v[0]), sizeof(T)*startElem, sizeof(T)*numOfElems);
    }

    template <typename T>
    void copy_from_sys_mem(T* pSource, u32 numOfElems)
    {
        copy_raw_from_sys_mem(pSource, 0, numOfElems);
    }

    template <typename T>
    void copy_from_sys_mem(T* pSource, u32 startElem, u32 numOfElems)
    {
        copy_raw_from_sys_mem((void*)(pSource), sizeof(T)*startElem, sizeof(T)*numOfElems);
    }



protected:


};

} // ::revel::renderer
} // ::revel

#endif // VERTEXBUFFER_H
