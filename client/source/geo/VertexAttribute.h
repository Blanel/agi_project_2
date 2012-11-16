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

enum class VertexAttribType
{
    FLOAT32 = 0x1,
    FLOAT32_2 = 0x2,
    FLOAT32_3 = 0x3,
    FLOAT32_4 = 0x4,
    UNDEFINED
};

class VertexAttribBase
{
protected:
    std::string m_Name;
    VertexAttribType m_Type;

    VertexAttribBase(const std::string& name, VertexAttribType type = VertexAttribType::UNDEFINED)
        : m_Name(name)
        , m_Type(type)
    {}

public:
    virtual ~VertexAttribBase() {}    

    const std::string& name() const;
    VertexAttribType type() const;

    virtual u32 size_in_bytes() = 0;
    virtual void* raw_data_ptr() = 0;
};

template <typename T>
class VertexAttrib : public VertexAttribBase
{
    std::vector<T> m_VertexData;

    void init();

public:
    VertexAttrib(const std::string &name, u32 capacity = 0) 
        : VertexAttribBase(name)
        , m_VertexData(capacity) 
    {
        init();
    }

    std::vector<T>& data() { return m_VertexData; }

    u32 size_in_bytes() { return sizeof(T) * m_VertexData.size(); }

    void* raw_data_ptr() { return &m_VertexData[0]; }
};

template <typename T>
void VertexAttrib<T>::init()
{
    m_Type = VertexAttribType::UNDEFINED;
}

template <>
void VertexAttrib<f32>::init();

template <>
void VertexAttrib<point3_f32>::init();

template <>
void VertexAttrib<vec2_f32>::init();

template <>
void VertexAttrib<vec3_f32>::init();

template <>
void VertexAttrib<vec4_f32>::init();



typedef std::shared_ptr<VertexAttribBase> VertexAttribPtr;
typedef std::vector<VertexAttribPtr> VertexAttribArray;


}


#endif // VERTEXATTRIBUTE_H
