#ifndef TEXTURESAMPLER_H
#define TEXTURESAMPLER_H

#include "Types.h"
#include "renderer/GpuObject.h"

namespace revel
{
namespace renderer
{

enum class TextureMinFilter
{
    NEAREST,
    LINEAR
};

enum class TextureMagFilter
{
    NEAREST,
    LINEAR
};

enum class TextureWrap
{
    CLAMP,
    REPEAT,
    MIRRORED_REPEAT
};

class TextureSampler
    : public GpuObject
{
protected:
    TextureMinFilter m_MinFilter;
    TextureMagFilter m_MagFilter;
    TextureWrap m_WrapS;
    TextureWrap m_WrapT;
    f32 m_MaxAnistropy;

public:
    TextureSampler(TextureMinFilter min, TextureMagFilter mag, TextureWrap s, TextureWrap t, f32 ani = 0.0f);
    virtual ~TextureSampler();

    TextureMinFilter min_filter() const;
    TextureMagFilter mag_filter() const;
    TextureWrap wrap_s() const;
    TextureWrap wrap_t() const;
    f32 max_anistropy() const;

};

}
}

#endif // TEXTURESAMPLER_H
