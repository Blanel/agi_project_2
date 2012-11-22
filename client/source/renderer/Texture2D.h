#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "GpuObject.h"

namespace revel
{
namespace renderer
{

enum class TextureFormat
{
    RGB_U8,
    RGBA_U8,
    RGB_F32,
    RGBA_F32
};

class Texture2D : public GpuObject
{
    u32             m_Width;
    u32             m_Height;
    TextureFormat   m_InternalFormat;
    bool            m_MipMapped;

public:
    Texture2D(u32 w, u32 h, TextureFormat format, bool mimap = true);

    u32 width() const { return m_Width; }
    u32 height() const { return m_Height; }
    bool has_mipmap() { return m_MipMapped; }
    TextureFormat format() const { return m_InternalFormat; }

    virtual void bind() = 0;
    virtual void unbind() = 0;
};

} // ::revel::renderer
} // ::revel

#endif // TEXTURE2D_H
