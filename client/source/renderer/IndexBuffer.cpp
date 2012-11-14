#include "IndexBuffer.h"

namespace revel
{
namespace renderer
{

IndexBuffer::IndexBuffer(BufferHint hint, u32 size)
    : m_Hint(hint)
    , m_SizeInBytes(size)
{

}

IndexBuffer::~IndexBuffer()
{

}

}
}
