#ifndef DRAWSTATE_H
#define DRAWSTATE_H

#include <memory>

namespace revel
{
namespace renderer
{

class RenderState;
class GpuProgram;
class VertexArrayState;

class DrawState
{
    std::weak_ptr<RenderState>      m_pRenderState;
    std::weak_ptr<GpuProgram>       m_pGpuProgram;
    std::weak_ptr<VertexArrayState> m_pVertexArrayState;

public:
    DrawState(const std::shared_ptr<RenderState>& rs, const std::shared_ptr<GpuProgram>& gpuprog, const std::shared_ptr<VertexArrayState>& vao);

    bool operator<(const DrawState& state)
    {
        if (m_pGpuProgram.lock().get() < state.m_pGpuProgram.lock().get())
            return true;
        else
            return false;
    }

    //Render state
    const std::weak_ptr<RenderState>& render_state() { return m_pRenderState; }

    //Shader state
    const std::weak_ptr<GpuProgram>& gpu_program() { return m_pGpuProgram; }

    //Vertex state
    const std::weak_ptr<VertexArrayState>& vertex_array_state() { return m_pVertexArrayState; }
};

} // ::revel::renderer
} // ::revel

#endif // DRAWSTATE_H
