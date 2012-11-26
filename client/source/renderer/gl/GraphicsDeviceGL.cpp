#include "RenderWindowGL.h"
#include "renderer/gl/GraphicsDeviceGL.h"
#include "renderer/gl/IndexBufferGL.h"
#include "renderer/gl/VertexBufferGL.h"
#include "renderer/gl/ShaderObjectGL.h"
#include "renderer/gl/ShaderProgramGL.h"
#include "renderer/gl/TextureSamplerGL.h"
#include "renderer/gl/Texture2DGL.h"

#include <stdexcept>
#include <fstream>
#include <iostream>
#include <memory>

namespace revel
{
namespace renderer
{
namespace gl
{

GraphicsDeviceGL::GraphicsDeviceGL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        R_LOG_INFO("Couldn't initialize SDL (VIDEO)");
        throw std::exception();
    }

    m_APIName = "OpenGL";
    m_APIVersion = "0.0.0";
}

GraphicsDeviceGL::~GraphicsDeviceGL()
{
}

std::shared_ptr<RenderWindow> 
GraphicsDeviceGL::create_window(u32 w, u32 h, const std::string& title)
{
    return std::make_shared<RenderWindowGL>(w, h, title);
}

std::shared_ptr<VertexBuffer>
GraphicsDeviceGL::create_vertex_buffer(BufferHint hint, u32 size)
{
    return std::make_shared<VertexBufferGL>(hint, size);
}

std::shared_ptr<IndexBuffer>
GraphicsDeviceGL::create_index_buffer(BufferHint hint, u32 size)
{
    return std::make_shared<IndexBufferGL>(hint, size);
}

/*
std::shared_ptr<Texture2D> 
GraphicsDeviceGL::create_texture_2d(const Image2D<T>& img)
{
    //img
    return std::make_shared<Texture2DGL>();
}
*/

std::shared_ptr<Texture2D>
GraphicsDeviceGL::create_texture_2d(const Texture2DDesc& description)
{
    return nullptr;
}

std::shared_ptr<ShaderProgram>
GraphicsDeviceGL::create_shader_program(const std::string& vs, const std::string& fs, const std::string& gs)
{
    ShaderObjectGL vertex(ShaderType::VERTEX, vs);
    ShaderObjectGL fragment(ShaderType::FRAGMENT, fs);
    ShaderObjectGL geometry(ShaderType::GEOMETRY, gs);

    R_LOG_ERR("Not yet implementet");

    return nullptr;
}

std::shared_ptr<ShaderProgram>
GraphicsDeviceGL::create_shader_program(const std::string& vs, const std::string& fs)
{
    return std::make_shared<ShaderProgramGL>(vs, fs);
}

std::shared_ptr<ShaderProgram>
GraphicsDeviceGL::create_shader_program_from_file(const std::string &vsf, const std::string &fsf)
{
    std::string vertexsource;
    std::string fragmentsource;

    std::ifstream in_vsf(vsf);

    while (in_vsf.good())
    {
        std::string buffer;
        std::getline(in_vsf, buffer);

        vertexsource += buffer;
        vertexsource += "\n";
    }

    in_vsf.close();

    std::ifstream in_fsf(fsf);

    while (in_fsf.good())
    {
        std::string buffer;
        std::getline(in_fsf, buffer);

        fragmentsource += buffer;
        fragmentsource += "\n";
    }

    in_fsf.close();

    //R_LOG_INFO("\nVertex Source: \n" << vertexsource);
    //R_LOG_INFO("\nFragment Source: \n" << fragmentsource);

    return std::make_shared<ShaderProgramGL>(vertexsource, fragmentsource);
}


std::shared_ptr<TextureSampler>
GraphicsDeviceGL::create_texture_sampler(TextureMinFilter min, TextureMagFilter mag, TextureWrap wraps, TextureWrap wrapt, f32 ani)
{
    return std::make_shared<TextureSamplerGL>(min, mag, wraps, wrapt, ani);
}


GLint
GraphicsDeviceGL::max_texture_units()
{
    GLint value;
    ::glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &value);
    //::glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &value);
    return value;
}

GLint
GraphicsDeviceGL::max_vertex_attribs()
{
    GLint value;
    ::glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &value);
    return value;
}

const std::string&
GraphicsDeviceGL::api_name()
{
    return m_APIName;
}

const std::string&
GraphicsDeviceGL::api_version()
{
    return m_APIVersion;
}

} // ::revel::renderer::gl
} // ::revel::renderer
} // ::revel

