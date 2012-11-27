#include "renderer/gl/UniformGL.h"

namespace revel
{
namespace renderer
{
namespace gl
{




template<>
UniformGL<f32>& UniformGL<f32>::operator=(const f32& value)
{
    if (value != m_Value)
    {
 		set_value(value);
    }

    return *this;
}

template<>
UniformGL<vec2>& UniformGL<vec2>::operator=(const vec2& value)
{
    if (value != m_Value)
    {
 		set_value(value);
    }

    return *this;
}

template<>
UniformGL<vec3>& UniformGL<vec3>::operator=(const vec3& value)
{
    if (value != m_Value)
    {
 		set_value(value);
    }

    return *this;
}

template<>
UniformGL<vec4>& UniformGL<vec4>::operator=(const vec4& value)
{
    if (value != m_Value)
    {
 		set_value(value);
    }

    return *this;
}

template<>
UniformGL<point3>& UniformGL<point3>::operator=(const point3& value)
{
    if (value != m_Value)
    {
        set_value(value);
    }

    return *this;
}

template<>
UniformGL<math::mat3>& UniformGL<math::mat3>::operator=(const math::mat3& value)
{
    if (value != m_Value)
    {
 		set_value(value);
    }

    return *this;
}

template<>
UniformGL<math::mat4>& UniformGL<math::mat4>::operator=(const math::mat4& value)
{
    if (value != m_Value)
    {
 		set_value(value);
    }
    
    return *this;
}

template<>
void UniformGL<f32>::set_value(const f32& value)
{
	m_Value = value;
    ::glUniform1f(m_Location, m_Value);
}

template<>
void UniformGL<vec2>::set_value(const vec2& value)
{
	m_Value = value;
    ::glUniform2f(m_Location, m_Value.x, m_Value.y);
}

template<>
void UniformGL<vec3>::set_value(const vec3& value)
{
	m_Value = value;
    ::glUniform3f(m_Location, m_Value.x, m_Value.y, m_Value.z);
}

template<>
void UniformGL<vec4>::set_value(const vec4& value)
{
	m_Value = value;
    ::glUniform4f(m_Location, m_Value.x, m_Value.y, m_Value.z, m_Value.w);
}

template<>
void UniformGL<point3>::set_value(const point3& value)
{
    m_Value = value;
    ::glUniform3f(m_Location, m_Value.x, m_Value.y, m_Value.z);
}

template<>
void UniformGL<math::mat3>::set_value(const math::mat3& value)
{
	m_Value = value;
    ::glUniformMatrix3fv(m_Location, 1, GL_TRUE, &value.e[0]);
}

template<>
void UniformGL<math::mat4>::set_value(const math::mat4& value)
{
	m_Value = value;
    ::glUniformMatrix4fv(m_Location, 1, GL_TRUE, &value.e[0]);       
}

}
}
}
