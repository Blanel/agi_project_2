#include "RenderContext.h"

namespace revel
{
namespace renderer
{
	
std::shared_ptr<VertexArray>
RenderContext::create_vertex_array(const std::shared_ptr<geo::Mesh>& pMesh)
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

        switch (it->type())
        {
            case VertexAttribType::FLOAT32:
                num_of_components = 1;
                datatype = ComponentDatatype::FLOAT32;
            break;
            case VertexAttribType::FLOAT32_2:
                num_of_components = 2;
                datatype = ComponentDatatype::FLOAT32;
            break;
            case VertexAttribType::FLOAT32_3:
                num_of_components = 3;
                datatype = ComponentDatatype::FLOAT32;
            break;
            case VertexAttribType::FLOAT32_4:
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

    return va;
}

} // ::revel::renderer

} // ::revel
