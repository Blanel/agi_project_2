#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "GpuObject.h"
#include "Image2D.h"

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
    bool            m_BuildMipMap;

public:
    Texture2D();
    Texture2D(u32 w, u32 h, TextureFormat format, bool mimap = true);

    u32 width() const { return m_Width; }
    u32 height() const { return m_Height; }
    bool build_mipmap() { return m_BuildMipMap; }
    TextureFormat format() const { return m_InternalFormat; }

    //virtual void copy_raw_from_sys_mem() = 0;

    template <typename T>
    void copy_from_sys_mem(const Image2D<T>& img)
    {
        this->bind();

    }

    virtual void bind() = 0;
    virtual void unbind() = 0;
};

} // ::revel::renderer
} // ::revel

#endif // TEXTURE2D_H
