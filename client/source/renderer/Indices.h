#ifndef INDICES_H
#define INDICES_H

#include "Types.h"
#include <vector>
#include <memory>

namespace revel
{

enum class IndexType
{
    UNDEFINED,
    U8,
    U16,
    U32
};

namespace detail
{

class IndicesBase
{
protected:
    IndexType m_Type;

public:
    IndexType type() { return m_Type; }

    IndicesBase() {}
    virtual ~IndicesBase() {}

    virtual void add_triangle(u32 a, u32 b, u32 c) = 0;
    virtual u32 count() = 0;
};

template <typename T>
class Indices : public IndicesBase
{
protected:
    std::vector<T> m_Indices;

public:
    Indices(IndexType type) {}
    virtual ~Indices() {}

    virtual void add_triangle(u32 a, u32 b, u32 c) { m_Indices.push_back(a); m_Indices.push_back(b); m_Indices.push_back(c); }
    virtual u32 count() { return m_Indices.size(); }
    std::vector<T>& data() { return m_Indices; }
    const std::vector<T>& data() const { return m_Indices; }
};

} // ::revel::detail

class IndicesU16
    : public detail::Indices<u16>
{
public:
    IndicesU16()
        : detail::Indices<u16>(IndexType::U16)
    {

    }
};

class IndicesU32
    : public detail::Indices<u32>
{
public:
    IndicesU32()
        : detail::Indices<u32>(IndexType::U32)
    {

    }
};

typedef IndicesU16 indices_u16;
typedef IndicesU32 indices_u32;

typedef std::shared_ptr<detail::IndicesBase> IndicesPtr;


} // ::revel

#endif // INDICES_H
