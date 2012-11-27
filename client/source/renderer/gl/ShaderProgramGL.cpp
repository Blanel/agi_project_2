#include <GL/glew.h>

#include "renderer/GpuException.h"
#include "renderer/gl/ShaderProgramGL.h"
#include "renderer/gl/ShaderObjectGL.h"
#include "renderer/ShaderVertexAttrib.h"

#include "Log.h"

namespace revel
{
namespace renderer
{
namespace gl
{

ShaderProgramGL::ShaderProgramGL(const std::string& vs, const std::string& fs)
{
    R_LOG_INFO("Creating an OpenGL shader program.");

    m_Identifier = ::glCreateProgram();

    ShaderObjectGL sh_vertex(ShaderType::VERTEX, vs);
    ShaderObjectGL sh_fragment(ShaderType::FRAGMENT, fs);

    ::glAttachShader(m_Identifier, sh_vertex.m_Identifier);
    ::glAttachShader(m_Identifier, sh_fragment.m_Identifier);

    this->link();

    if (!this->is_valid())
        throw GpuException("Could not create a valid OpenGL shader program");

    setup_attributes();
    setup_uniforms();
}

ShaderProgramGL::ShaderProgramGL(const std::string& vs, const std::string& fs, const std::string& gs)
{
    m_Identifier = ::glCreateProgram();

    ShaderObjectGL sh_vertex(ShaderType::VERTEX, vs);
    ShaderObjectGL sh_fragment(ShaderType::FRAGMENT, fs);
    ShaderObjectGL sh_geometry(ShaderType::GEOMETRY, gs);

    ::glAttachShader(m_Identifier, sh_vertex.m_Identifier);
    ::glAttachShader(m_Identifier, sh_fragment.m_Identifier);
    ::glAttachShader(m_Identifier, sh_geometry.m_Identifier);

    if (!this->is_valid())
        throw GpuException("Could not create a valid OpenGL shader program");

    this->link();
}

ShaderProgramGL::~ShaderProgramGL()
{
    ::glDeleteProgram(m_Identifier);
}

void
ShaderProgramGL::use()
{
    ::glUseProgram(m_Identifier);
}

bool
ShaderProgramGL::link()
{
    ::glLinkProgram(m_Identifier);

    GLint status;

    ::glGetProgramiv(m_Identifier, GL_LINK_STATUS, &status);

    if (status == GL_FALSE)
    {
        R_LOG_ERR("Failed to link shader program");

        GLint loglength;

        ::glGetProgramiv(m_Identifier, GL_INFO_LOG_LENGTH, &loglength);

        if (loglength > 0)
        {
            char* log = (char*)malloc(loglength);
            GLsizei written;

            ::glGetProgramInfoLog(m_Identifier, loglength, &written, log);

            R_LOG_ERR("Program log: " << log);
            free(log);
        }
    }


    return false;
}

void
ShaderProgramGL::setup_attributes()
{
    GLint nAttribs, maxlength;
    ::glGetProgramiv(m_Identifier, GL_ACTIVE_ATTRIBUTES, &nAttribs);
    ::glGetProgramiv(m_Identifier, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxlength);


    GLchar* name = (GLchar*) malloc(maxlength);

    GLint size, loc;
    GLsizei written;
    GLenum type;

    R_LOG_INFO("\nATTRIBUTES (" << nAttribs << "): \n");

    for (int i = 0; i < nAttribs; ++i)
    {
        ::glGetActiveAttrib(m_Identifier, i, maxlength, &written, &size, &type, name);
        loc = ::glGetAttribLocation(m_Identifier, name);

        ShaderVertexAttribType shadertype;

        switch(type)
        {
        case GL_FLOAT:
            shadertype = ShaderVertexAttribType::FLOAT32; break;
        case GL_FLOAT_VEC2:
            shadertype = ShaderVertexAttribType::FLOAT32_2; break;
        case GL_FLOAT_VEC3:
            shadertype = ShaderVertexAttribType::FLOAT32_3; break;
        case GL_FLOAT_VEC4:
            shadertype = ShaderVertexAttribType::FLOAT32_4; break;

        default:
            throw GpuException("Unhandled shader vertex attribute type.");
        }

        m_Attributes.insert(std::make_pair(name, ShaderVertexAttrib(name, loc, shadertype)));

        R_LOG_INFO("\n" << loc << "\t" << name);
    }

    free(name);
}

void
ShaderProgramGL::setup_uniforms()
{
    GLint nUniforms, maxlength;

    ::glGetProgramiv(m_Identifier, GL_ACTIVE_UNIFORMS, &nUniforms);
    ::glGetProgramiv(m_Identifier, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxlength);

    GLchar* name = (GLchar*)malloc(maxlength);

    GLint size, loc;
    GLsizei written;
    GLenum type;

    std::cout << "UNIFORMS: " << nUniforms << std::endl;

    for (int i = 0; i < nUniforms; ++i)
    {
        ::glGetActiveUniform(m_Identifier, i, maxlength, &written, &size, &type, name);
        loc = ::glGetUniformLocation(m_Identifier, name);

        R_LOG_INFO("Uniform location: " << loc);

        switch (type)
        {
        case GL_FLOAT:
            m_Uniforms[name] = std::unique_ptr<UniformGL<f32>>(new UniformGL<f32>(loc, name, 0)); break;
        case GL_FLOAT_VEC2:
            m_Uniforms[name] = std::unique_ptr<UniformGL<vec2>>(new UniformGL<vec2>(loc, name, vec2::Zero)); break;
        case GL_FLOAT_VEC3:
            m_Uniforms[name] = std::unique_ptr<UniformGL<vec3>>(new UniformGL<vec3>(loc, name, vec3::Zero)); break;
        case GL_FLOAT_VEC4:
            m_Uniforms[name] = std::unique_ptr<UniformGL<vec4>>(new UniformGL<vec4>(loc, name, vec4::Zero)); break;
        case GL_FLOAT_MAT3:
            m_Uniforms[name] = std::unique_ptr<UniformGL<math::mat3>>(new UniformGL<math::mat3>(loc, name, math::mat3::Identity)); break;
        case GL_FLOAT_MAT4:
            m_Uniforms[name] = std::unique_ptr<UniformGL<math::mat4>>(new UniformGL<math::mat4>(loc, name, math::mat4::Identity)); break;

        default:
            throw GpuException("Unknown type in OpenGL GLSL Uniform");
        }
    }

    free(name);
}

} // ::revel::renderer::gl
} // ::revel::renderer
} // ::revel

