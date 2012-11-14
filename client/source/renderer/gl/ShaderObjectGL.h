#ifndef SHADERSOURCE_H
#define SHADERSOURCE_H

#include "Types.h"

#include <string>
#include "renderer/ShaderType.h"

namespace revel
{
namespace renderer
{
namespace gl
{

class ShaderObjectGL
{
public:
    ShaderObjectGL(ShaderType type, const std::string& source);
    virtual ~ShaderObjectGL();

protected:
    void compile();
    bool is_compiled();

    u32 m_Identifier;
    ShaderType m_Type;
    std::string m_Source;

    friend class ShaderProgramGL;
};

} // ::revel::renderer::gl
} // ::revel::renderer
} // ::revel

#endif // SHADERSOURCE_H
