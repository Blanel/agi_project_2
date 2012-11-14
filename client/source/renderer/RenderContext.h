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

#include "Device.h"
#include "Types.h"

namespace revel
{

class Entity;

namespace renderer
{

class Framebuffer;
//class RenderWindow;

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

    virtual VertexArrayPtr create_vertex_array() = 0;
    virtual VertexArrayPtr create_vertex_array(const std::shared_ptr<geo::Mesh>& pMesh)
    {
        R_LOG_INFO("Creating vertex array from mesh.");

        auto va = create_vertex_array();
        va->bind();

        //read all attributes and create vertex buffers
        auto attribs = pMesh->vertex_attrib_array();

        for (auto it : attribs)
        {
            i32 num_of_components;
            ComponentDatatype datatype;

            auto type = it->type();

            switch (type)
            {
                case VertexAttributeType::FLOAT32:
                    num_of_components = 1;
                    datatype = ComponentDatatype::FLOAT32;
                break;
                case VertexAttributeType::VEC2_F32:
                case VertexAttributeType::FLOAT32_2:
                    num_of_components = 2;
                    datatype = ComponentDatatype::FLOAT32;
                break;
                case VertexAttributeType::VEC3_F32:
                case VertexAttributeType::FLOAT32_3:
                    num_of_components = 3;
                    datatype = ComponentDatatype::FLOAT32;
                break;
                case VertexAttributeType::VEC4_F32:
                case VertexAttributeType::FLOAT32_4:
                    num_of_components = 4;
                    datatype = ComponentDatatype::FLOAT32;
                break;
                default:
                R_LOG_ERR("Unknown attribute type.");
            }

            u32 buffersize = it->size_in_bytes();


            auto vbuffer = Device::graphics()->create_vertex_buffer(BufferHint::STATIC_DRAW, buffersize);
            vbuffer->copy_raw_from_sys_mem(it->raw_data_ptr(), 0, buffersize);

            auto& pAttrib = va->create_attrib(it->name(), vbuffer, datatype, num_of_components);
        }

        //build an index buffer

        auto iptr = pMesh->index_array();

        if (iptr != nullptr)
        {
            R_LOG_INFO("Building index array for VA");

            switch(pMesh->index_array()->type())
            {
                case IndexType::U16:
                {
                    auto indices = pMesh->indices<u16>();
                    auto ibuffer = Device::graphics()->create_index_buffer(BufferHint::STATIC_DRAW, indices->count() * sizeof(u16));
                    ibuffer->copy_from_sys_mem(indices->data());
                    va->set_index_buffer(ibuffer);
                }
                break;
                case IndexType::U32:
                {
                    auto indices = pMesh->indices<u32>();
                    auto ibuffer = Device::graphics()->create_index_buffer(BufferHint::STATIC_DRAW, indices->count() * sizeof(u32));
                    ibuffer->copy_from_sys_mem(indices->data());
                    va->set_index_buffer(ibuffer);
                }
                break;
            }
        }

        va->unbind();

        return va;
    }

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

    virtual void draw(const std::shared_ptr<geo::Mesh>& mesh) = 0;
    virtual void draw(const std::shared_ptr<VertexBuffer>& vbo) = 0;
};


} // ::revel::renderer
} // ::revel

#endif // RENDERCONTEXT_H_
