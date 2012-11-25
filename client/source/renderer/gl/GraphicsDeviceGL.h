#ifndef GRAPHICSDEVICEGL_H
#define GRAPHICSDEVICEGL_H

#include "renderer/GraphicsDevice.h"
#include "renderer/BufferHint.h"
#include <memory>

namespace revel
{
namespace renderer
{

enum class BufferHint;
class RenderWindow;

namespace gl
{

class IndexBufferGL;
class VertexBufferGL;


class GraphicsDeviceGL : public GraphicsDevice
{
public:
    GraphicsDeviceGL();
    virtual ~GraphicsDeviceGL();

    virtual std::shared_ptr<RenderWindow> create_window(u32 w, u32 h, const std::string& title) override;
    virtual std::shared_ptr<VertexBuffer> create_vertex_buffer(BufferHint hint, u32 size) override;
    virtual std::shared_ptr<IndexBuffer> create_index_buffer(BufferHint hint, u32 size) override;
    virtual std::shared_ptr<Texture2D> create_texture_2d(const Texture2DDesc& description) override;

    virtual std::shared_ptr<ShaderProgram> create_shader_program(const std::string& fs, const std::string& vs, const std::string& gs) override;
    virtual std::shared_ptr<ShaderProgram> create_shader_program(const std::string& fs, const std::string& vs) override;
    virtual std::shared_ptr<ShaderProgram> create_shader_program_from_file(const std::string &vsf, const std::string &fsf) override;
    virtual std::shared_ptr<TextureSampler> create_texture_sampler(TextureMinFilter min, TextureMagFilter mag, TextureWrap wraps, TextureWrap wrapt, f32 ani) override;
    virtual i32 max_texture_units() override;
    virtual i32 max_vertex_attribs() override;
    virtual const std::string& api_name() override;
    virtual const std::string& api_version() override;

};

} // ::revel::renderer::gl
} // ::revel::renderer
} // ::revel

#endif // GRAPHICSDEVICEGL_H
