#ifndef VERTEXARRAYGL_H
#define VERTEXARRAYGL_H

#include "renderer/gl/VertexBufferAttribGL.h"
#include "renderer/gl/IndexBufferGL.h"
#include "renderer/VertexArray.h"

namespace revel
{
namespace renderer
{
namespace gl
{


class VertexArrayGL : public VertexArray
{
public:
    VertexArrayGL();
    virtual ~VertexArrayGL();

    void bind();
    void unbind();

    std::unique_ptr<VertexBufferAttrib>& create_attrib(u32 index, const std::shared_ptr<VertexBuffer>& buffer, ComponentDatatype type, u32 numOfComponents)
    {
        m_Attributes.push_back(std::unique_ptr<VertexBufferAttrib>(new VertexBufferAttribGL(index, buffer, type, numOfComponents)));
        return m_Attributes.back();
    }

    std::unique_ptr<VertexBufferAttrib>& create_attrib(u32 index, const std::string& name, const std::shared_ptr<VertexBuffer>& buffer, ComponentDatatype type, u32 numOfComponents)
    {
        auto& ptr = create_attrib(index, buffer, type, numOfComponents);
        m_AttribMap[name] = ptr.get();
        return ptr;
    }

    void set_index_buffer(const std::shared_ptr<IndexBuffer> &buffer);

};

} // ::revel::renderer::gl
} // ::revel::renderer
} // ::revel


#endif // VERTEXARRAYGL_H
