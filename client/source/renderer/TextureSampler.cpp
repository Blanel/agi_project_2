#include "TextureSampler.h"

namespace revel
{
namespace renderer
{

TextureSampler::TextureSampler(TextureMinFilter min, TextureMagFilter mag, TextureWrap s, TextureWrap t, f32 ani)
    : m_MinFilter(min)
    , m_MagFilter(mag)
    , m_WrapS(s)
    , m_WrapT(t)
    , m_MaxAnistropy(ani)
{
}

TextureSampler::TextureSampler(TextureMinFilter min, TextureMagFilter mag, TextureWrap s, TextureWrap t, TextureWrap r, f32 ani)
    : m_MinFilter(min)
    , m_MagFilter(mag)
    , m_WrapS(s)
    , m_WrapT(t)
    , m_WrapR(r)
    , m_MaxAnistropy(ani)
{
}


TextureSampler::~TextureSampler()
{

}

TextureMinFilter
TextureSampler::min_filter() const
{
    return m_MinFilter;
}

TextureMagFilter
TextureSampler::mag_filter() const
{
    return m_MagFilter;
}

TextureWrap
TextureSampler::wrap_s() const
{
    return m_WrapS;
}

TextureWrap
TextureSampler::wrap_t() const
{
    return m_WrapT;
}

TextureWrap
TextureSampler::wrap_r() const
{
    return m_WrapT;
}

f32
TextureSampler::max_anistropy() const
{
    return m_MaxAnistropy;
}


}
}

