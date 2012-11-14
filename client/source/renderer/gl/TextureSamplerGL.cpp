#include "TextureSamplerGL.h"
#include <GL/glew.h>


namespace revel
{
namespace renderer
{
namespace gl
{

TextureSamplerGL::TextureSamplerGL(TextureMinFilter min, TextureMagFilter mag, TextureWrap s, TextureWrap t, f32 ani)
    : TextureSampler(min, mag, s, t, ani)
{
    ::glGenSamplers(1, &m_Identifier);

    set_min_filter(min);
    set_mag_filter(mag);
    set_texture_wrap_s(s);
    set_texture_wrap_t(t);
}

TextureSamplerGL::~TextureSamplerGL()
{
    ::glDeleteSamplers(1, &m_Identifier);
}

void
TextureSamplerGL::set_mag_filter(TextureMagFilter mag)
{
    m_MagFilter = mag;

    switch (mag)
    {
    case TextureMagFilter::NEAREST:
        ::glSamplerParameteri(m_Identifier, GL_TEXTURE_MAG_FILTER, GL_NEAREST); break;
    case TextureMagFilter::LINEAR:
        ::glSamplerParameteri(m_Identifier, GL_TEXTURE_MAG_FILTER, GL_LINEAR); break;
    }
}

void
TextureSamplerGL::set_min_filter(TextureMinFilter min)
{
    m_MinFilter = min;

    switch (min)
    {
    case TextureMinFilter::NEAREST:
        ::glSamplerParameteri(m_Identifier, GL_TEXTURE_MIN_FILTER, GL_NEAREST); break;
    case TextureMinFilter::LINEAR:
        ::glSamplerParameteri(m_Identifier, GL_TEXTURE_MIN_FILTER, GL_LINEAR); break;
    }
}

void
TextureSamplerGL::set_texture_wrap_s(TextureWrap wrap)
{
    m_WrapS = wrap;

    switch (wrap)
    {
    case TextureWrap::CLAMP:
        ::glSamplerParameteri(m_Identifier, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); break;
    case TextureWrap::REPEAT:
        ::glSamplerParameteri(m_Identifier, GL_TEXTURE_WRAP_S, GL_REPEAT); break;
    case TextureWrap::MIRRORED_REPEAT:
        ::glSamplerParameteri(m_Identifier, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); break;
    }
}

void
TextureSamplerGL::set_texture_wrap_t(TextureWrap wrap)
{
    m_WrapS = wrap;

    switch (wrap)
    {
    case TextureWrap::CLAMP:
        ::glSamplerParameteri(m_Identifier, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); break;
    case TextureWrap::REPEAT:
        ::glSamplerParameteri(m_Identifier, GL_TEXTURE_WRAP_T, GL_REPEAT); break;
    case TextureWrap::MIRRORED_REPEAT:
        ::glSamplerParameteri(m_Identifier, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT); break;
    }
}

} // ::revel::renderer::gl
} // ::revel::renderer
} // ::revel
