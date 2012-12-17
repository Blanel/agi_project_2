#ifndef RENDERCONTEXTGL_H_
#define RENDERCONTEXTGL_H_

#include "renderer/RenderContext.h"

namespace revel
{
namespace renderer
{
namespace gl
{

class RenderWindowGL;

class RenderContextGL : public RenderContext
{
public:
	RenderContextGL(RenderWindowGL* win);
    virtual ~RenderContextGL();

    void make_current();

    virtual std::shared_ptr<VertexArray> create_vertex_array() override;
    virtual std::shared_ptr<Framebuffer> create_framebuffer() override;

    virtual void clear(const std::shared_ptr<ClearState> &cs) override;
    virtual void clear(const ClearState& cs) override;

    virtual void draw(PrimitiveType type, const std::shared_ptr<DrawState>& drawstate, const std::shared_ptr<SceneState>& scenestate);
    virtual void draw(const std::shared_ptr<geo::Mesh>& mesh) override;
    virtual void draw(const std::shared_ptr<VertexBuffer>& vbo) override;

protected:
    RenderWindowGL* m_pWindow;
    SDL_GLContext m_ContextHandle;
};

} // ::revel::renderer::gl
} // ::revel::renderer
} // ::revel


#endif // RENDERCONTEXTGL_H_
