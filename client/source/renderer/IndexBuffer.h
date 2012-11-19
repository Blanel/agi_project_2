#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include "GpuObject.h"
#include "BufferHint.h"

#include <vector>

namespace revel
{
namespace renderer
{

class IndexBuffer
    : public GpuObject
{
public:
    enum class Datatype
    {
        UINT8,
        UINT16,
        UINT32
    };

protected:
    BufferHint m_Hint;
    u32 m_SizeInBytes;
    Datatype m_Datatype;

    virtual void copy_raw_from_sys_mem(void* pSource, u32 offsetInByte, u32 lengthInByte) = 0;

public:
    IndexBuffer(BufferHint hint, u32 size);
    virtual ~IndexBuffer();

    virtual void bind() = 0;
    virtual void unbind() = 0;

    Datatype get_datatype() const
    {
        return m_Datatype;
    }

    u32 size_in_bytes() const 
    { 
        return m_SizeInBytes;
    }

    u32 count() const 
    { 
        if (m_Datatype == Datatype::UINT8)
            return size_in_bytes();
        else if (m_Datatype == Datatype::UINT16)
            return size_in_bytes() / 2;
        else if (m_Datatype == Datatype::UINT32)
            return size_in_bytes() / 4;
        else
            return size_in_bytes();
    }

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
        copy_raw_from_sys_mem(static_cast<void*>(pSource), sizeof(T)*startElem, sizeof(T)*numOfElems);
    }

};

}
}

#endif // INDEXBUFFER_H
