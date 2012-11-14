#ifndef UNIFORMGL_H
#define UNIFORMGL_H

#include "Types.h"
#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Vector4.h"
#include "math/Matrix3x3.h"
#include "math/Matrix4x4.h"
#include "renderer/Uniform.h"
#include <GL/glew.h>

#include "Log.h"
#include <memory>

namespace revel
{
namespace renderer
{
namespace gl
{

class UniformBlock
{
    GLuint m_BlockIndex;
    GLint m_BlockSize;

};



class UniformGL_f32
    : public UniformT<f32>
{
    i32 m_Location;

public:
    UniformGL_f32(i32 loc, const std::string& name, f32 value)
        : UniformT<f32>(name, UniformDatatype::FLOAT32)
        , m_Location(loc)
    {
        m_Value = value;
    }

    UniformGL_f32& operator=(const f32& value)
    {
        if (value != m_Value)
        {
            m_Value = value;
            ::glUniform1f(m_Location, m_Value);
        }
    }

};

class UniformGL_vec2
    : public UniformT<vec2>
{
    i32 m_Location;

public:
    UniformGL_vec2(i32 loc, const std::string& name, const vec2& value)
        : UniformT<vec2>(name, UniformDatatype::VEC2_F32)
        , m_Location(loc)
    {
        m_Value = value;
    }

    UniformGL_vec2& operator=(const vec2& value)
    {
        if (value != m_Value)
        {
            m_Value = value;
            ::glUniform2f(m_Location, m_Value.x, m_Value.y);
        }
    }
};


class UniformGL_vec3
    : public UniformT<vec3>
{
    i32 m_Location;

public:
    UniformGL_vec3(i32 loc, const std::string& name, const vec3& value)
        : UniformT<vec3>(name, UniformDatatype::VEC3_F32)
        , m_Location(loc)
    {
        m_Value = value;
    }

    UniformGL_vec3& operator=(const vec3& value)
    {
        if (value != m_Value)
        {
            m_Value = value;
            ::glUniform3f(m_Location, m_Value.x, m_Value.y, m_Value.z);
        }
    }

};


class UniformGL_vec4
    : public UniformT<vec4>
{
    i32 m_Location;

public:
    UniformGL_vec4(i32 loc, const std::string& name, const vec4& value)
        : UniformT<vec4>(name, UniformDatatype::VEC4_F32)
        , m_Location(loc)
    {
        m_Value = value;
    }

    UniformGL_vec4& operator=(const vec4& value)
    {
        if (value != m_Value)
        {
            m_Value = value;
            ::glUniform4f(m_Location, m_Value.x, m_Value.y, m_Value.z, m_Value.w);
        }
    }
};

class UniformGL_mat3
    : public UniformT<math::mat3>
{
    i32 m_Location;

public:
    UniformGL_mat3(i32 loc, const std::string& name, const math::mat3_f32& value = math::mat3_f32::Identity)
        : UniformT<math::mat3_f32>(name, UniformDatatype::MAT3_F32)
        , m_Location(loc)
    {
        m_Value = value;
        ::glUniformMatrix3fv(m_Location, 1, GL_TRUE, &value.e[0]);
    }

    UniformGL_mat3& operator=(const math::mat3& value)
    {
        if (value != m_Value)
        {
            m_Value = value;
            ::glUniformMatrix3fv(m_Location, 1, GL_TRUE, &value.e[0]);
        }
    }
};

class UniformGL_mat4
    : public UniformT<math::mat4>
{
    i32 m_Location;

public:
    UniformGL_mat4(i32 loc, const std::string& name, const math::mat4& value)
        : UniformT<math::mat4>(name, UniformDatatype::MAT4_F32)
        , m_Location(loc)
    {
    }

    UniformGL_mat4& operator=(const math::mat4& value)
    {

        ::glUniformMatrix4fv(m_Location, 1, GL_TRUE, &value.e[0]);
        return *this;
    }
};


}
}
}


#endif // UNIFORMGL_H
