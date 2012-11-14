#ifndef RENDERSTATE_H
#define RENDERSTATE_H


#include "Blending.h"
#include "DepthMask.h"
#include "DepthRange.h"
#include "DepthTest.h"
#include "PrimitiveRestart.h"
#include "ProgramPointSize.h"
#include "ScissorTest.h"
#include "StencilTest.h"
#include "ColorMask.h"


namespace revel
{
namespace renderer
{

enum class RasterizationMode
{
    Point,
    Line,
    Fill
};


/**
 * TODO: Add bitmask for renderstate sorting.
 */
class RenderState
{
    Blending            m_Blending;
    ColorMask           m_ColorMask;
    DepthMask           m_DepthMask;
    DepthRange          m_DepthRange;
    DepthTest           m_DepthTest;
    PrimitiveRestart    m_PrimitiveRestart;
    ProgramPointSize    m_ProgramPointSize;
    RasterizationMode   m_RasterizationMode;
    ScissorTest         m_ScissorTest;
    StencilTest         m_StencilTest;

public:
    RenderState() {}

    Blending& blending() { return m_Blending; }
    ColorMask& color_mask() { return m_ColorMask; }
    DepthMask& depth_mask() { return m_DepthMask; }
    DepthRange& depth_range() { return m_DepthRange; }
    DepthTest& depth_test() { return m_DepthTest; }

    PrimitiveRestart& primitive_restart() { return m_PrimitiveRestart; }
    ProgramPointSize& program_point_size() { return m_ProgramPointSize; }
    RasterizationMode& rasterization_mode() { return m_RasterizationMode; }

    ScissorTest& scissor_test() { return m_ScissorTest; }
    StencilTest& stencil_test() { return m_StencilTest; }

};

} // ::revel::renderer
} // ::revel

#endif // RENDERSTATE_H
