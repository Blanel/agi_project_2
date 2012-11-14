#include "geo/VertexAttribute.h"

namespace revel
{

namespace detail
{

VertexAttributeBase::VertexAttributeBase(const std::string &name, VertexAttributeType type)
    : m_Name(name)
    , m_Type(type)
{
}

const std::string&
VertexAttributeBase::name() const
{
    return m_Name;
}

VertexAttributeType
VertexAttributeBase::type() const
{
    return m_Type;
}

}

}
