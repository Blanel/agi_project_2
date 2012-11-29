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


template <typename T>
class UniformGL : public Uniform<T>
{
    i32 m_Location;

public:
    UniformGL(i32 loc, const std::string& name, const T& value)
        : Uniform<T>(name, UniformDatatype::UNDEFINED)
        , m_Location(loc)
    {
        set_value(value);
    }

    void set_value(const T& value);
    UniformGL& operator=(const T& value);
};

#ifndef _MSC_VER

template <>   
UniformGL<f32>::UniformGL(i32 loc, const std::string& name, const f32& value);

template <>   
UniformGL<i32>::UniformGL(i32 loc, const std::string& name, const i32& value);

template <>   
UniformGL<vec2>::UniformGL(i32 loc, const std::string& name, const vec2& value);

template <>   
UniformGL<vec3>::UniformGL(i32 loc, const std::string& name, const vec3& value);

template <>   
UniformGL<vec4>::UniformGL(i32 loc, const std::string& name, const vec4& value);

template <>   
UniformGL<point3>::UniformGL(i32 loc, const std::string& name, const point3& value);

template <>   
UniformGL<math::mat3>::UniformGL(i32 loc, const std::string& name, const math::mat3& value);

template <>   
UniformGL<math::mat4>::UniformGL(i32 loc, const std::string& name, const math::mat4& value);

#else 

template <>   
UniformGL<f32>::UniformGL(i32 loc, const std::string& name, const f32& value)
    : Uniform<f32>(name, UniformDatatype::FLOAT32)
    , m_Location(loc)
{
    set_value(value);
}

template <>   
UniformGL<i32>::UniformGL(i32 loc, const std::string& name, const i32& value)
    : Uniform<i32>(name, UniformDatatype::INT32)
    , m_Location(loc)
{
    set_value(value);
}

template <>   
UniformGL<vec2>::UniformGL(i32 loc, const std::string& name, const vec2& value)
    : Uniform<vec2>(name, UniformDatatype::VEC2_F32)
    , m_Location(loc)
{
    set_value(value);
}

template <>   
UniformGL<vec3>::UniformGL(i32 loc, const std::string& name, const vec3& value)
    : Uniform<vec3>(name, UniformDatatype::VEC3_F32)
    , m_Location(loc)
{
    set_value(value);
}

template <>   
UniformGL<vec4>::UniformGL(i32 loc, const std::string& name, const vec4& value)
    : Uniform<vec4>(name, UniformDatatype::VEC4_F32)
    , m_Location(loc)
{
    set_value(value);
}

template <>   
UniformGL<point3>::UniformGL(i32 loc, const std::string& name, const point3& value)
    : Uniform<point3>(name, UniformDatatype::VEC3_F32)
    , m_Location(loc)
{
    set_value(value);
}

template <>   
UniformGL<math::mat3>::UniformGL(i32 loc, const std::string& name, const math::mat3& value)
    : Uniform<math::mat3>(name, UniformDatatype::MAT3_F32)
    , m_Location(loc)
{
    set_value(value);
}

template <>   
UniformGL<math::mat4>::UniformGL(i32 loc, const std::string& name, const math::mat4& value)
    : Uniform<math::mat4>(name, UniformDatatype::MAT4_F32)
    , m_Location(loc)
{
    set_value(value);
}
#endif


template<>
UniformGL<f32>& UniformGL<f32>::operator=(const f32& value);

template<>
UniformGL<i32>& UniformGL<i32>::operator=(const i32& value);

template<>
UniformGL<vec2>& UniformGL<vec2>::operator=(const vec2& value);

template<>
UniformGL<vec3>& UniformGL<vec3>::operator=(const vec3& value);

template<>
UniformGL<vec4>& UniformGL<vec4>::operator=(const vec4& value);

template<>
UniformGL<point3>& UniformGL<point3>::operator=(const point3& value);

template<>
UniformGL<math::mat3>& UniformGL<math::mat3>::operator=(const math::mat3& value);

template<>
UniformGL<math::mat4>& UniformGL<math::mat4>::operator=(const math::mat4& value);

template<>
void UniformGL<f32>::set_value(const f32& value);

template<>
void UniformGL<i32>::set_value(const i32& value);

template<>
void UniformGL<vec2>::set_value(const vec2& value);

template<>
void UniformGL<vec3>::set_value(const vec3& value);

template<>
void UniformGL<vec4>::set_value(const vec4& value);

template<>
void UniformGL<point3>::set_value(const point3& value);

template<>
void UniformGL<math::mat3>::set_value(const math::mat3& value);

template<>
void UniformGL<math::mat4>::set_value(const math::mat4& value);

} // ::revel::renderer::gl
} // ::revel::renderer
} // ::revel


#endif // UNIFORMGL_H
