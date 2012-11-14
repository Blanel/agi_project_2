#include "ClearState.h"

namespace revel
{
namespace renderer
{

ClearState::ClearState()
    : m_ScissorTest()
    , m_ColorMask()
    , m_DepthMask()
    , m_FrontStencilMask()
    , m_BackStencilMask()
    , m_Buffers(ClearBuffers::ALL)
    , m_Color(0.3f, 0.4f, 0.5f, 1.0f)
    , m_Depth(1.0f)
    , m_Stencil(1)
{
}

} // ::revel::renderer
} // ::revel
