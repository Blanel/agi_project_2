#include "TextureUnitGL.h"

namespace revel
{
namespace renderer
{
namespace gl
{
//Intentionally left blank

TextureUnitGL::TextureUnitGL(u32 n)
{
    switch (n)
    {
    case 0:
        m_TextureUnitGL = GL_TEXTURE0; break;
    case 1:
        m_TextureUnitGL = GL_TEXTURE1; break;
    case 2:
        m_TextureUnitGL = GL_TEXTURE2; break;
    case 3:
        m_TextureUnitGL = GL_TEXTURE3; break;
    case 4:
        m_TextureUnitGL = GL_TEXTURE4; break;
    case 5:
        m_TextureUnitGL = GL_TEXTURE5; break;
    case 6:
        m_TextureUnitGL = GL_TEXTURE6; break;
    case 7:
        m_TextureUnitGL = GL_TEXTURE7; break;
    case 8:
        m_TextureUnitGL = GL_TEXTURE8; break;
    case 9:
        m_TextureUnitGL = GL_TEXTURE9; break;
    case 10:
        m_TextureUnitGL = GL_TEXTURE10; break;
    case 11:
        m_TextureUnitGL = GL_TEXTURE11; break;
    case 12:
        m_TextureUnitGL = GL_TEXTURE12; break;
    case 13:
        m_TextureUnitGL = GL_TEXTURE13; break;
    case 14:
        m_TextureUnitGL = GL_TEXTURE14; break;
    case 15:
        m_TextureUnitGL = GL_TEXTURE15; break;
    case 16:
        m_TextureUnitGL = GL_TEXTURE16; break;
    case 17:
        m_TextureUnitGL = GL_TEXTURE17; break;
    case 18:
        m_TextureUnitGL = GL_TEXTURE18; break;
    case 19:
        m_TextureUnitGL = GL_TEXTURE19; break;
    case 20:
        m_TextureUnitGL = GL_TEXTURE20; break;
    case 21:
        m_TextureUnitGL = GL_TEXTURE21; break;
    case 22:
        m_TextureUnitGL = GL_TEXTURE22; break;
    case 23:
        m_TextureUnitGL = GL_TEXTURE23; break;
    case 24:
        m_TextureUnitGL = GL_TEXTURE24; break;
    case 25:
        m_TextureUnitGL = GL_TEXTURE25; break;
    case 26:
        m_TextureUnitGL = GL_TEXTURE26; break;
    case 27:
        m_TextureUnitGL = GL_TEXTURE27; break;
    case 28:
        m_TextureUnitGL = GL_TEXTURE28; break;
    case 29:
        m_TextureUnitGL = GL_TEXTURE29; break;
    case 30:
        m_TextureUnitGL = GL_TEXTURE30; break;
    case 31:
        m_TextureUnitGL = GL_TEXTURE31; break;


    }


}

void
TextureUnitGL::set_texture(const std::shared_ptr<Texture2D> &tex)
{
    m_pTexture = tex;


}

void
TextureUnitGL::set_texture_sampler(const std::shared_ptr<TextureSampler> &sampler)
{
    m_pSampler = sampler;
}

}
}
}
