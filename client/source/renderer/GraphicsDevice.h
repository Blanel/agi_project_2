#ifndef GRAPHICSDEVICE_H
#define GRAPHICSDEVICE_H

#include <memory>
#include <string>

#include "Types.h"
// #include "renderer/VertexBuffer.h"
// #include "renderer/IndexBuffer.h"
// #include "renderer/ShaderProgram.h"
// #include "renderer/Texture2D.h"
// #include "renderer/TextureSampler.h"
#include "RenderWindow.h"

namespace revel
{
namespace renderer
{

//forward decl
enum class BufferHint;
//class RenderWindow;
class Texture2D;
class VertexBuffer;
class IndexBuffer;
class Texture2D;
class Texture2DDesc;
class TextureSampler;
class ShaderProgram;
enum class TextureMinFilter;
enum class TextureMagFilter;
enum class TextureWrap;
//class GpuBuffer;
//class RenderWindow;

/**
 * @class GraphicsDevice
 *
 * @brief Graphics device that creates render objects.
 */
class GraphicsDevice
{
protected:
    std::string m_APIName;
    std::string m_APIVersion;

public:
    GraphicsDevice();
    virtual ~GraphicsDevice();

    /**
     * @brief Create a render window with a graphics context.
     *
     * @param w Width.
     * @param h Height.
     * @param title Window title.
     */
    virtual std::shared_ptr<RenderWindow>       create_window(u32 w, u32 h, const std::string& title) = 0;

    /**
     * @brief Create a vertex buffer on the GPU.
     *
     * @param hint Hint for the GPU driver.
     * @param size Reserve buffer size.
     */
    virtual std::shared_ptr<VertexBuffer>       create_vertex_buffer(BufferHint hint, u32 size) = 0;

    /**
     * @brief Create an index buffer on the GPU.
     *
     * @param hint Hint for the GPU driver.
     * @param size Reserve buffer size.
     */
    virtual std::shared_ptr<IndexBuffer>        create_index_buffer(BufferHint hint, u32 size) = 0;

    /**
     * @brief Create a 2d texture object on the GPU.
     *
     * @param desc Texture object description.
     */
    virtual std::shared_ptr<Texture2D>          create_texture_2d(const Texture2DDesc& desc) = 0;

    /**
     * @brief Create a GPU shader program.
     *
     * @param vs Vertex shader source.
     * @param fs Fragment (pixel) shader source.
     * @param gs Geometry shader source.
     */
    virtual std::shared_ptr<ShaderProgram>      create_shader_program(const std::string& vs,
                                                                      const std::string& fs,
                                                                      const std::string& gs) = 0;

    /**
     * @brief Create a GPU shader program.
     *
     * @param vs Vertex shader source.
     * @param fs Fragment (pixel) shader source.
     */
    virtual std::shared_ptr<ShaderProgram>      create_shader_program(const std::string& vs,
                                                                      const std::string& fs) = 0;

    /**
     * @brief Create a GPU shader program from source files.
     *
     * @param vsf Vertex shader file.
     * @param fsf Fragment (pixel) shader file.
     */
    virtual std::shared_ptr<ShaderProgram>      create_shader_program_from_file(const std::string& vsf,
                                                                                const std::string& fsf) = 0;

    /**
     * @brief Create a texture sampler.
     *
     * @param min Texture minification filter.
     * @param max Texture magnification filter.
     * @param wraps Texture wrap method in s direction
     * @param wrapt Texture wrap method in t direction
     * @param ani Maximum anistropy.
     */
    virtual std::shared_ptr<TextureSampler>     create_texture_2d_sampler(TextureMinFilter min,
                                                                          TextureMagFilter mag,
                                                                          TextureWrap wraps,
                                                                          TextureWrap wrapt,
                                                                          f32 ani = 0.0f) = 0;

    virtual i32                               	max_texture_units() = 0;
    virtual i32                               	max_vertex_attribs() = 0;

    virtual const std::string&					api_name() = 0;
    virtual const std::string&					api_version() = 0;

};

} // ::revel::renderer
} // ::revel

#endif // GRAPHICSDEVICE_H
