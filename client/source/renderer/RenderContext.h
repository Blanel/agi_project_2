#ifndef RENDERCONTEXT_H_
#define RENDERCONTEXT_H_

#include "SDL.h"
#include "Color.h"
#include "geo/Rectangle.h"
#include "geo/Mesh.h"
#include <memory>

#include "renderer/TextureUnit.h"
#include "renderer/ClearState.h"
#include "renderer/VertexArray.h"
#include "renderer/GraphicsDevice.h"
#include "PrimitiveType.h"

#include "Device.h"
#include "Types.h"

namespace revel
{

class Entity;

namespace renderer
{

class Framebuffer;
//class RenderWindow;

class DrawState;
class SceneState;

class RenderContext
{
protected:
    geo::Rect_f32                               m_Viewport;
    //Color4<f32>                                 m_ClearColor;

    std::shared_ptr<Framebuffer>                m_pFramebuffer;
    std::shared_ptr<ClearState>                 m_pClearState;

    std::vector<std::unique_ptr<TextureUnit>>   m_TextureUnits;

public:
    RenderContext() {}
    virtual ~RenderContext() {}

    virtual void make_current() = 0;

    geo::Rect_f32 viewport() { return m_Viewport; }
    void set_viewport(const geo::Rect_f32& viewport) { m_Viewport = viewport; }

    virtual std::shared_ptr<VertexArray> create_vertex_array() = 0;
    virtual std::shared_ptr<VertexArray> create_vertex_array(const std::shared_ptr<geo::Mesh>& pMesh);

/*
    virtual std::shared_ptr<VertexArray> create_vertex_array(const std::shared_ptr<geo::Mesh>& pMesh, const std::shared_ptr<ShaderProgram>& sp)
    {
        auto va = create_vertex_array();
    }
*/
    /*

    virtual void create_framebuffer() = 0;
    virtual void create_vertex_array_state() = 0;

    virtual const std::shared_ptr<Framebuffer>& get_framebuffer() = 0;
    virtual void set_framebuffer(const std::shared_ptr<Framebuffer>& fb) = 0;
    */

    virtual void clear(const std::shared_ptr<ClearState>& cs) = 0;
    virtual void clear(const ClearState& cs) = 0;

    virtual void draw(PrimitiveType type, const std::shared_ptr<DrawState>& drawstate, const std::shared_ptr<SceneState>& scenestate) = 0;
    virtual void draw(const std::shared_ptr<geo::Mesh>& mesh) = 0;
    virtual void draw(const std::shared_ptr<VertexBuffer>& vbo) = 0;
};


} // ::revel::renderer
} // ::revel

#endif // RENDERCONTEXT_H_
