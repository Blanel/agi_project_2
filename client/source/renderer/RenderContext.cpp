#include "RenderContext.h"
#include "geo/Mesh.h"

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

        auto vbo = Device::graphics()->create_vertex_buffer(BufferHint::STATIC_DRAW, buffersize);
        vbo->copy_raw_from_sys_mem(it->raw_data_ptr(), 0, buffersize);

        auto& pAttrib = va->create_attrib(it->name(), vbo, datatype, num_of_components);
	}

    auto indexsize = pMesh->indices<u32>()->size_in_bytes();

    auto ibo = Device::graphics()->create_index_buffer(BufferHint::STATIC_DRAW, indexsize);
    ibo->copy_from_sys_mem(pMesh->indices<u32>()->data());
    va->set_index_buffer(ibo);

    return va;
}

} // ::revel::renderer

} // ::revel
