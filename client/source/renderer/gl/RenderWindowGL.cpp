#include "RenderWindowGL.h"
#include "RenderContextGL.h"
#include "SDL_video.h"

namespace revel
{
namespace renderer
{
namespace gl
{

RenderWindowGL::RenderWindowGL(u32 w, u32 h, const std::string& title)
    : RenderWindow(w, h, title)
{
    m_pSDLWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    m_pContext = std::make_shared<gl::RenderContextGL>(this);
}

void
RenderWindowGL::grab_input(bool enable)
{
    if (enable)
        SDL_SetWindowGrab(m_pSDLWindow, SDL_TRUE);
    else
        SDL_SetWindowGrab(m_pSDLWindow, SDL_FALSE);
}

void
RenderWindowGL::show_cursor(bool enable)
{
    SDL_ShowCursor(enable);
}

void
RenderWindowGL::set_mouse_position(u32 x, u32 y)
{
    SDL_WarpMouseInWindow(m_pSDLWindow, x, y);
}

void
RenderWindowGL::center_mouse_position()
{
    SDL_WarpMouseInWindow(m_pSDLWindow, width()/2, height()/2);
}

void
RenderWindowGL::toggle_input_grab()
{
    SDL_bool enable = SDL_GetWindowGrab(m_pSDLWindow);

    //SDL_SetWindowGrab(m_pSDLWindow, !enable);

    if (enable)
        SDL_SetWindowGrab(m_pSDLWindow, SDL_FALSE);
    else
        SDL_SetWindowGrab(m_pSDLWindow, SDL_TRUE);
}

} // ::revel::renderer::gl
} // ::revel::renderer
} // ::revel
