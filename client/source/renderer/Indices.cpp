#include "Indices.h"

namespace revel
{
	
template <>
void Indices<u8>::init()
{
    m_Type = IndexType::U8;
}

template <>
void Indices<u16>::init()
{
    m_Type = IndexType::U16;
}

template <>
void Indices<u32>::init()
{
    m_Type = IndexType::U32;
}

} // ::revel