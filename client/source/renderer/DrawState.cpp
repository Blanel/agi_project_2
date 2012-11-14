#include "DrawState.h"

namespace revel
{
namespace renderer
{

DrawState::DrawState(const std::shared_ptr<RenderState> &rs, const std::shared_ptr<GpuProgram> &gpuprog, const std::shared_ptr<VertexArrayState> &vao)
    : m_pRenderState(rs)
    , m_pGpuProgram(gpuprog)
    , m_pVertexArrayState(vao)
{
}

} // ::revel::renderer
} // ::revel

