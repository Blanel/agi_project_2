#ifndef SHADERVERTEXATTRIB_H
#define SHADERVERTEXATTRIB_H

#include "../Types.h"
#include <string>

namespace revel
{
namespace renderer
{

enum class ShaderVertexAttribType
{
    FLOAT32,
    FLOAT32_2,
    FLOAT32_3,
    FLOAT32_4,
    FLOAT32_2x2,
    FLOAT32_3x3,
    FLOAT32_4x4
};

class ShaderVertexAttrib
{
protected:
    std::string m_Name;
    i32 m_Location;
    ShaderVertexAttribType m_Type;
    i32 m_Length;

public:
    ShaderVertexAttrib(const std::string& name, i32 loc, ShaderVertexAttribType type);

    const std::string& name() const;
    i32 location() const;
    ShaderVertexAttribType type() const;
    i32 length() const;
};

}
}

#endif // SHADERVERTEXATTRIB_H
