#ifndef INDICES_H
#define INDICES_H

#include "Types.h"
#include <vector>
#include <memory>

namespace revel
{

enum class IndexType
{
    U8,
    U16,
    U32,
    UNDEFINED
};

class IndicesBase
{
protected:
    IndexType m_Type;

public:
    IndexType type() { return m_Type; }

    IndicesBase() {}
    virtual ~IndicesBase() {}

    //virtual void add_triangle(u8 a, u8 b, u8 c) = 0;
    //virtual void add_triangle(u16 a, u16 b, u16 c) = 0;
    virtual void add_triangle(u32 a, u32 b, u32 c) = 0;
    virtual u32 size_in_bytes() const = 0;
    virtual u32 count() const = 0;
};

template <typename T>
class Indices : public IndicesBase
{
    std::vector<T> m_Indices;
    void init();

public:
    Indices(u32 capacity = 0) : m_Indices(capacity) { init(); }
    virtual ~Indices() {}

    //virtual void add_triangle(u8 a, u8 b, u8 c) { m_Indices.push_back(a); m_Indices.push_back(b); m_Indices.push_back(c); }
    //virtual void add_triangle(u16 a, u16 b, u16 c) { m_Indices.push_back(a); m_Indices.push_back(b); m_Indices.push_back(c); }
    virtual void add_triangle(u32 a, u32 b, u32 c) { m_Indices.push_back(a); m_Indices.push_back(b); m_Indices.push_back(c); }

    virtual u32 count() const { return m_Indices.size(); }
    virtual u32 size_in_bytes() const { return sizeof(T) * count(); }

    std::vector<T>& data() { return m_Indices; }
    const std::vector<T>& data() const { return m_Indices; }
};

template <typename T>
void Indices<T>::init()
{
    m_Type = IndexType::UNDEFINED;
}

template <>
void Indices<u8>::init();

template <>
void Indices<u16>::init();

template <>
void Indices<u32>::init();

typedef std::shared_ptr<IndicesBase> IndicesPtr;


} // ::revel

#endif // INDICES_H
