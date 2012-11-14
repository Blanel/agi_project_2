#include "ShaderVertexAttrib.h"

namespace revel
{
namespace renderer
{

ShaderVertexAttrib::ShaderVertexAttrib(const std::string &name, i32 loc, ShaderVertexAttribType type)
    : m_Name(name)
    , m_Location(loc)
    , m_Type(type)
{
}

const std::string&
ShaderVertexAttrib::name() const
{
    return m_Name;
}

i32
ShaderVertexAttrib::location() const
{
    return m_Location;
}

i32
ShaderVertexAttrib::length() const
{
    return m_Length;
}

ShaderVertexAttribType
ShaderVertexAttrib::type() const
{
    return m_Type;
}


}
}

