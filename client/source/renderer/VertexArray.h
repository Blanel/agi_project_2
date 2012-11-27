#ifndef VERTEXARRAY_H_
#define VERTEXARRAY_H_


#include "renderer/GpuObject.h"
#include <vector>
#include <memory>
#include <map>

#include "renderer/VertexComponent.h"
#include "renderer/VertexBufferAttrib.h"
#include "renderer/IndexBuffer.h"
#include "Device.h"

namespace revel
{
namespace renderer
{

class VertexBufferAttrib;
class VertexBuffer;
class IndexBuffer;
//class Mesh;

/**
 * @brief Vertex array state.
 * Encapsulate the vertex array state on the client side
 *
 * Currently OpenGL specific (VAO), for DirectX implementation compare it with Vertex Declarations
 */
class VertexArray : public GpuObject
{
protected:
    std::vector<std::unique_ptr<VertexBufferAttrib>> m_Attributes;
    std::map<std::string, VertexBufferAttrib*> m_AttribMap;
    std::shared_ptr<IndexBuffer> m_pIndexBuffer;
    u32 m_IndexCount;

public:
    VertexArray();

    virtual ~VertexArray();

    virtual void bind() = 0;
    virtual void unbind() = 0;

    virtual const std::unique_ptr<VertexBufferAttrib>& create_attrib(u32 index,
                                                                     const std::shared_ptr<VertexBuffer>& buffer,
                                                                     ComponentDatatype type,
                                                                     u32 ncomponents) = 0;

    virtual const std::unique_ptr<VertexBufferAttrib>& create_attrib(u32 index,
                                                                     const std::string& name,
                                                                     const std::shared_ptr<VertexBuffer>& buffer,
                                                                     ComponentDatatype type,
                                                                     u32 ncomponents) = 0;

    /*
    virtual const std::unique_ptr<VertexBufferAttrib>& create_attrib(const std::shared_ptr<VertexBuffer>& buffer,
                                                                     ComponentDatatype type,
                                                                     u32 numOfComponents,
                                                                     u32 stride,
                                                                     u32 offset,
                                                                     bool normalize = false) = 0;
    */

    bool has_index_buffer() const;

    u32 index_count() const;

    VertexBufferAttrib* attrib(const std::string& name);

    virtual void set_index_buffer(const std::shared_ptr<IndexBuffer>& buffer) = 0;
    //virtual void set_vertex_attrib_array(u32 index, const std::shared_ptr<VertexBuffer>& buffer, i32 numOfComponents, bool normalize = false, u32 offset = 0) = 0;

    /*
    virtual void set_vertex_attrib(u32 index, f32 x) = 0;
    virtual void set_vertex_attrib(u32 index, f32 x, f32 y) = 0;
    virtual void set_vertex_attrib(u32 index, f32 x, f32 y, f32 z) = 0;
    virtual void set_vertex_attrib(u32 index, f32 x, f32 y, f32 z, f32 w) = 0;

    virtual void enable_vertex_attrib_array(u32 index, bool enable = true) = 0;

    */
};

typedef std::shared_ptr<VertexArray> VertexArrayPtr;

} // ::revel::renderer
} // ::revel


#endif // VERTEXARRAY_H_
