#include "renderer/gl/GraphicsDeviceGL.h"
#include "renderer/gl/RenderContextGL.h"
#include "renderer/gl/RenderWindowGL.h"
#include "renderer/gl/VertexArrayGL.h"
#include "renderer/gl/TextureUnitGL.h"
#include "renderer/gl/FramebufferGL.h"

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Vector4.h"

#include <cassert>
#include <GL/glew.h>
#include <iostream>
#include <memory>

#include "renderer/DrawState.h"
#include "renderer/SceneState.h"

#include "renderer/GpuException.h"
#include "Device.h"

using namespace std;
using namespace revel::math;

namespace revel
{
namespace renderer
{
namespace gl
{

RenderContextGL::RenderContextGL(RenderWindowGL *win)
{
    assert(win);
    m_pWindow = win;
	glewExperimental = GL_TRUE;
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetSwapInterval(0); 


    m_ContextHandle = SDL_GL_CreateContext(win->m_pSDLWindow);

    GLenum err = glewInit();

    if (err)
    {
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;

        throw GpuException("GLEW failed to initialize");
    }

    for (u32 i = 0; i < Device::graphics()->max_texture_units(); ++i)
    {
        m_TextureUnits.push_back(std::unique_ptr<TextureUnitGL>(new TextureUnitGL(i)));
    }

    ::glViewport(0, 0, win->width(), win->height());
}

RenderContextGL::~RenderContextGL()
{
    SDL_GL_DeleteContext(m_ContextHandle);
}

void
RenderContextGL::make_current()
{
    SDL_GL_MakeCurrent(m_pWindow->m_pSDLWindow, m_ContextHandle);
}

void
RenderContextGL::clear(const std::shared_ptr<ClearState>& clearstate)
{
	clear(*(clearstate.get()));
}

void
RenderContextGL::clear(const ClearState& clearstate)
{
    GLbitfield bufferbits = 0;
    ClearBuffers cb = clearstate.buffers();

    if (cb == ClearBuffers::COLOR)
        bufferbits = GL_COLOR_BUFFER_BIT;
    else if (cb == ClearBuffers::DEPTH)
        bufferbits = GL_DEPTH_BUFFER_BIT;
    else if (cb == ClearBuffers::STENCIL)
        bufferbits = GL_STENCIL_BUFFER_BIT;
    else if (cb == ClearBuffers::ALL)
        bufferbits = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;

    ::glClearDepth(clearstate.depth());

    ::glClearStencil(clearstate.stencil());

    ::glClearColor(clearstate.color().r(),
                   clearstate.color().g(),
                   clearstate.color().b(),
                   clearstate.color().a());

    ::glClear(bufferbits);
}

std::shared_ptr<VertexArray>
RenderContextGL::create_vertex_array()
{
    return std::make_shared<VertexArrayGL>();
}

std::shared_ptr<Framebuffer>
RenderContextGL::create_framebuffer()
{
    return std::make_shared<FramebufferGL>();
}

void
RenderContextGL::draw(PrimitiveType type, const std::shared_ptr<DrawState>& drawstate, const std::shared_ptr<SceneState>& scenestate)
{
    R_LOG_ERR("Not yet implemented");
}

void
RenderContextGL::draw(const std::shared_ptr<geo::Mesh> &mesh)
{
    R_LOG_ERR("Not yet implemented");
}

void
RenderContextGL::draw(const std::shared_ptr<VertexBuffer>& vbo)
{
    R_LOG_ERR("Not yet implemented");

    //vbo->bind();

    //::glDrawArrays(GL_POINTS, 0, 8);

    //vbo->unbind();
}

} // ::revel::renderer::gl
} // ::revel::renderer
} // ::revel

