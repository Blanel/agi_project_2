#ifndef CLEARSTATE_H
#define CLEARSTATE_H

#include "ScissorTest.h"
#include "ColorMask.h"
#include "DepthMask.h"
#include "Color.h"
//#include ""

namespace revel
{
namespace renderer
{

enum class ClearBuffers
{
    COLOR = 0x01,
    DEPTH = 0x02,
    STENCIL = 0x04,
    ALL = COLOR | DEPTH | STENCIL
};

class ClearState
{
    ScissorTest     m_ScissorTest;
    ColorMask       m_ColorMask;
    DepthMask       m_DepthMask;
    i32             m_FrontStencilMask;
    i32             m_BackStencilMask;

    ClearBuffers    m_Buffers;
    Color4<f32>     m_Color;
    f32             m_Depth;
    i32             m_Stencil;

public:
    ClearState();

    const ClearBuffers&     buffers() const { return m_Buffers; }
    const ScissorTest&      scissor_test() const { return m_ScissorTest; }
    const ColorMask&        color_mask() const { return m_ColorMask; }
    const DepthMask&        depth_mask() const { return m_DepthMask; }
    i32                     front_stencil_mask() const { return m_FrontStencilMask; }
    i32                     back_stencil_mask() const { return m_BackStencilMask; }
    const Color4<f32>&      color() const { return m_Color; }
    f32                     depth() const { return m_Depth; }
    i32                     stencil() const { return m_Stencil; }

    void set_buffers(const ClearBuffers& b) { m_Buffers = b; }
    void set_scissor_test(const ScissorTest& s) { m_ScissorTest = s; }
    void set_color_mask(const ColorMask& m) { m_ColorMask = m; }
    void set_depth_mask(const DepthMask& m) { m_DepthMask = m; }
    void set_front_stencil_mask(i32 m) { m_FrontStencilMask = m; }
    void set_back_stencil_mask(i32 m) { m_BackStencilMask = m; }
    void set_color(const Color4<f32>& c) { m_Color = c; }
    void set_depth(f32 x) { m_Depth = x; }
    void set_stencil(i32 x) { m_Stencil = x; }

};

} // ::revel::renderer
} // ::revel

#endif // CLEARSTATE_H
