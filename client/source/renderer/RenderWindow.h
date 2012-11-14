#ifndef RENDERWINDOW_H_
#define RENDERWINDOW_H_

#include <memory>
#include <string>

#include "Types.h"

namespace revel
{
namespace renderer
{

//forward decl
class RenderContext;

class RenderWindow
{
public:
    RenderWindow(u32 w, u32 h, const std::string& title);
    virtual ~RenderWindow();

    const std::shared_ptr<RenderContext>& context();

    virtual void swap_buffer() = 0;

    virtual void show_cursor(bool enable = true) = 0;

    virtual void grab_input(bool enable = true) = 0;

    virtual void toggle_input_grab() = 0;

    virtual void set_mouse_position(u32 x, u32 y) = 0;

    virtual void center_mouse_position() = 0;

    u32 width() { return m_Width; }
    u32 height() { return m_Height; }

protected:
    u32 m_Width;
    u32 m_Height;
    std::string m_Title;

    std::shared_ptr<RenderContext> m_pContext;
};

} // ::revel::renderer
} // ::revel

#endif // RENDERWINDOW_H_
