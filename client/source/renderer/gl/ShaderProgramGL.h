#ifndef GPUPROGRAMGL_H
#define GPUPROGRAMGL_H

#include "renderer/ShaderProgram.h"
#include "renderer/ShaderType.h"
#include "renderer/gl/UniformGL.h"

namespace revel
{
namespace renderer
{
namespace gl
{

class ShaderProgramGL : public ShaderProgram
{
public:
    ShaderProgramGL(const std::string& vs, const std::string& fs);
    ShaderProgramGL(const std::string& vs, const std::string& fs, const std::string& gs);
    virtual ~ShaderProgramGL();

    void use();

protected:
    void setup_uniforms();
    void setup_attributes();

    //std::unique_ptr<UniformBase> create_uniform();

    bool link();
};

} // ::revel::renderer::gl
} // ::revel::renderer
} // ::revel

#endif // GPUPROGRAMGL_H
