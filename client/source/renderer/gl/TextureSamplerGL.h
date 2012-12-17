#ifndef TEXTURESAMPLERGL_H
#define TEXTURESAMPLERGL_H

#include "renderer/TextureSampler.h"

namespace revel
{
namespace renderer
{
namespace gl
{

class TextureSamplerGL
    : public TextureSampler
{
    void set_min_filter(TextureMinFilter min);
    void set_mag_filter(TextureMagFilter mag);
    void set_texture_wrap_s(TextureWrap wrap);
    void set_texture_wrap_t(TextureWrap wrap);
    void set_texture_wrap_r(TextureWrap wrap);

public:
    TextureSamplerGL(TextureMinFilter min, TextureMagFilter mag, TextureWrap s, TextureWrap t, f32 ani = 0.0f);
    TextureSamplerGL(TextureMinFilter min, TextureMagFilter mag, TextureWrap s, TextureWrap t, TextureWrap r, f32 ani = 0.0f);
    virtual ~TextureSamplerGL();
};

} // ::revel::renderer::gl
} // ::revel::renderer
} // ::revel

#endif // TEXTURESAMPLERGL_H
