#ifndef VERTEXATTRIBUTE_H
#define VERTEXATTRIBUTE_H

#include <string>
#include <vector>
#include <memory>
#include "Types.h"
#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Vector4.h"

namespace revel
{

enum class VertexAttributeType
{
    FLOAT32,
    FLOAT32_2,
    FLOAT32_3,
    FLOAT32_4,
    VEC2_F32,
    VEC3_F32,
    VEC4_F32
};

namespace detail
{

class VertexAttributeBase
{
public:

protected:
    std::string m_Name;
    VertexAttributeType m_Type;

public:

    VertexAttributeBase(const std::string& name, VertexAttributeType type);

    const std::string& name() const;
    VertexAttributeType type() const;

    virtual u32 size_in_bytes() = 0;
    virtual void* raw_data_ptr() = 0;
};

template <typename T>
class VertexAttribute : public VertexAttributeBase
{
    std::vector<T> m_VertexData;

public:
    VertexAttribute(const std::string& name, VertexAttributeType type)
        : VertexAttributeBase(name, type)
        , m_VertexData()
    {
    }

    VertexAttribute(const std::string &name, VertexAttributeType type, u32 capacity)
        : VertexAttributeBase(name, type)
        , m_VertexData(capacity)
    {
    }

    std::vector<T>& data() { return m_VertexData; }

    u32 size_in_bytes() { return sizeof(T) * m_VertexData.size(); }

    void* raw_data_ptr() { return &m_VertexData[0]; }
};

} // ::revel::detail

class VertexAttribute_f32 : public detail::VertexAttribute<f32>
{
public:
    VertexAttribute_f32(const std::string& name)
        : VertexAttribute<f32>(name, VertexAttributeType::FLOAT32)
    {

    }

    VertexAttribute_f32(const std::string& name, u32 capacity)
        : VertexAttribute<f32>(name, VertexAttributeType::FLOAT32, capacity)
    {

    }

};

class VertexAttribute_vec2_f32 : public detail::VertexAttribute<vec2>
{
public:
    VertexAttribute_vec2_f32(const std::string& name)
        : detail::VertexAttribute<vec2>(name, VertexAttributeType::VEC2_F32)
    {

    }

    VertexAttribute_vec2_f32(const std::string& name, u32 capacity)
        : detail::VertexAttribute<vec2>(name, VertexAttributeType::VEC2_F32, capacity)
    {

    }

};

class VertexAttribute_vec3_f32 : public detail::VertexAttribute<vec3>
{
public:
    VertexAttribute_vec3_f32(const std::string& name)
        : detail::VertexAttribute<vec3>(name, VertexAttributeType::VEC3_F32)
    {

    }

    VertexAttribute_vec3_f32(const std::string& name, u32 capacity)
        : detail::VertexAttribute<vec3>(name, VertexAttributeType::VEC3_F32, capacity)
    {

    }

};

class VertexAttribute_point3_f32 : public detail::VertexAttribute<point3>
{
public:
    VertexAttribute_point3_f32(const std::string& name)
        : detail::VertexAttribute<point3>(name, VertexAttributeType::VEC3_F32)
    {

    }

    VertexAttribute_point3_f32(const std::string& name, u32 capacity)
        : detail::VertexAttribute<point3>(name, VertexAttributeType::VEC3_F32, capacity)
    {

    }

};

class VertexAttribute_vec4_f32 : public detail::VertexAttribute<vec4>
{
public:
    VertexAttribute_vec4_f32(const std::string& name)
        : detail::VertexAttribute<vec4>(name, VertexAttributeType::VEC4_F32)
    {

    }

    VertexAttribute_vec4_f32(const std::string& name, u32 capacity)
        : detail::VertexAttribute<vec4>(name, VertexAttributeType::VEC4_F32, capacity)
    {

    }

};

typedef std::shared_ptr<detail::VertexAttributeBase> VertexAttributePtr;
typedef std::vector<VertexAttributePtr> VertexAttribArray;

typedef VertexAttribute_f32      VAttr_f32;
typedef VertexAttribute_vec2_f32 VAttr_vec2;
typedef VertexAttribute_vec3_f32 VAttr_vec3;
typedef VertexAttribute_vec4_f32 VAttr_vec4;

typedef VertexAttribute_point3_f32 VAttr_point3;

typedef VertexAttribute_vec2_f32 VAttr_vec2_f32;
typedef VertexAttribute_vec3_f32 VAttr_vec3_f32;
typedef VertexAttribute_vec4_f32 VAttr_vec4_f32;

typedef VertexAttribute_vec4_f32 VAttr_vec4_f32;

}


#endif // VERTEXATTRIBUTE_H
