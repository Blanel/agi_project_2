#ifndef RENDERWINDOWGL_H_
#define RENDERWINDOWGL_H_

#include "Types.h"
#include "../RenderWindow.h"
//#include "renderer/gl/RenderContextGL.h"

#include "SDL.h"

namespace revel
{
namespace renderer
{
namespace gl
{

class RenderWindowGL : public renderer::RenderWindow
{
public:
    RenderWindowGL(u32 w, u32 h, const std::string& title);

    void swap_buffer() override { SDL_GL_SwapWindow(m_pSDLWindow); }
    virtual void show_cursor(bool enable = true) override;
    virtual void toggle_input_grab() override;
    virtual void set_mouse_position(u32 x, u32 y) override;
    virtual void center_mouse_position() override;
    virtual void grab_input(bool enable = true) override;

    friend class RenderContextGL;

protected:
    SDL_Window* m_pSDLWindow;

};

} // ::revel::renderer::gl
} // ::revel::renderer
} // ::revel

#endif // RENDERWINDOW_H_