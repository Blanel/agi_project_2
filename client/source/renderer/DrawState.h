#ifndef DRAWSTATE_H
#define DRAWSTATE_H

#include <memory>

namespace revel
{
namespace renderer
{


//forward decl
class RenderState;
class ShaderProgram;
class VertexArray;

class DrawState
{
    std::shared_ptr<RenderState>        m_pRenderState;
    std::shared_ptr<ShaderProgram>      m_pShaderProgram;
    std::shared_ptr<VertexArray>        m_pVertexArray;

public:
    DrawState(const std::shared_ptr<RenderState>& rs, const std::shared_ptr<ShaderProgram>& sp, const std::shared_ptr<VertexArray>& va)
        : m_pRenderState(rs)
        , m_pShaderProgram(sp)
        , m_pVertexArray(va)
    {

    }


/*
    bool operator<(const DrawState& state)
    {
        if (m_pShaderProgram.get() < state.m_pShaderProgram.get())
            return true;
        else
            return false;
    }
*/

    //Render state
    const std::shared_ptr<RenderState>& render_state() { return m_pRenderState; }

    //Shader state
    const std::shared_ptr<ShaderProgram>& shader_program() { return m_pShaderProgram; }

    //Vertex state
    const std::shared_ptr<VertexArray>& vertex_array() { return m_pVertexArray; }
};

} // ::revel::renderer
} // ::revel

#endif // DRAWSTATE_H
