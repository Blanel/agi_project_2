#ifndef SHADERTYPE_H
#define SHADERTYPE_H

namespace revel
{
namespace renderer
{

enum class ShaderType
{
    VERTEX,
    FRAGMENT,
    GEOMETRY,
    TESS_EVALUATION,
    TESS_CONTROL,
    UNKNOWN
};

} // ::revel::renderer
} // ::revel

#endif // SHADERTYPE_H
