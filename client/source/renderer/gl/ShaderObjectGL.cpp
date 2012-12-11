#include <GL/glew.h>

#include "renderer/GpuException.h"
#include "renderer/gl/ShaderObjectGL.h"

#include "Log.h"
#include <cstdlib>

namespace revel
{
namespace renderer
{
namespace gl
{

ShaderObjectGL::ShaderObjectGL(ShaderType type, const std::string& source)
    : m_Type(type)
    , m_Source(source)
{    
    switch(type)
    {
        case ShaderType::VERTEX:
            m_Identifier = ::glCreateShader(GL_VERTEX_SHADER);
        break;

        case ShaderType::FRAGMENT:
            m_Identifier = ::glCreateShader(GL_FRAGMENT_SHADER);
        break;

        case ShaderType::GEOMETRY:
            m_Identifier = ::glCreateShader(GL_GEOMETRY_SHADER);
        break;

        default:
            throw GpuException("Unknown shader format");
    }

    this->compile();

    GLint length, result;

    glGetShaderiv(m_Identifier, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE) {
        char *log;

        /* get the shader info log */
        glGetShaderiv(m_Identifier, GL_INFO_LOG_LENGTH, &length);
        log = (char*)malloc(length);
        glGetShaderInfoLog(m_Identifier, length, &result, log);

        /* print an error message and the info log */
        R_LOG_ERR("ShaderCompile: Unable to compile: " << log);
        free(log);

        //glDeleteShader(m_Identifier);
        //return 0;
    }

    if (!this->is_compiled())
        throw GpuException("Could not compile shader");
}

ShaderObjectGL::~ShaderObjectGL()
{
    if (m_Identifier)
        ::glDeleteShader(m_Identifier);
}

void
ShaderObjectGL::compile()
{
    const char* sourceptr = m_Source.c_str();

    ::glShaderSource(m_Identifier, 1, &sourceptr, 0);
    ::glCompileShader(m_Identifier);
}

bool
ShaderObjectGL::is_compiled()
{
    i32 compiled = 0;
    ::glGetObjectParameterivARB(m_Identifier, GL_OBJECT_COMPILE_STATUS_ARB, &compiled);

    return compiled;
}

} // ::revel::renderer::gl
} // ::revel::renderer
} // ::revel


