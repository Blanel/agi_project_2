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

class Texture2DDesc
{
private:
    u32             m_Width;
    u32             m_Height;
    bool            m_BuildMipMap;

    TextureFormat   m_InternalFormat;

public:
    Texture2DDesc(u32 w, u32 h, TextureFormat format, bool mipmap = true)
        : m_Width(w)
        , m_Height(h)
        , m_InternalFormat(format)
        , m_BuildMipMap(mipmap)
    {
    }

    u32 width() const { return m_Width; }
    u32 height() const { return m_Height; }
    bool build_mipmap() { return m_BuildMipMap; }
    TextureFormat format() const { return m_InternalFormat; }
};

class Texture2D : public GpuObject
{
public:
    Texture2D();
};

} // ::revel::renderer
} // ::revel

#endif // TEXTURE2D_H
