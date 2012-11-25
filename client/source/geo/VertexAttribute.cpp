#include "geo/VertexAttribute.h"

namespace revel
{

const std::string&
VertexAttribBase::name() const
{
    return m_Name;
}

VertexAttribType
VertexAttribBase::type() const
{
    return m_Type;
}

template <> 
void VertexAttrib<f32>::init()
{
    m_Type = VertexAttribType::FLOAT32;
};

template <>
void VertexAttrib<vec2_f32>::init()
{
    m_Type = VertexAttribType::FLOAT32_2;
};

template <> 
void VertexAttrib<vec3_f32>::init()
{
    m_Type = VertexAttribType::FLOAT32_3;
};

template <>
void VertexAttrib<vec4_f32>::init()
{
    m_Type = VertexAttribType::FLOAT32_4;
};

template <> 
void VertexAttrib<point3>::init()
{
    m_Type = VertexAttribType::FLOAT32_3;
};

}
