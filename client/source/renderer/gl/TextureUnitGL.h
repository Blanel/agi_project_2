#ifndef TEXTUREUNITGL_H
#define TEXTUREUNITGL_H

#include "renderer/TextureUnit.h"

namespace revel
{
namespace renderer
{
namespace gl
{

class TextureUnitGL
    : public TextureUnit
{
    GLenum m_TextureUnitGL;

public:
    TextureUnitGL(u32 n);

    void set_texture(const std::shared_ptr<Texture2D> &tex);
    void set_sampler(const std::shared_ptr<TextureSampler> &sampler);
    const std::shared_ptr<Texture2D>& texture();
    const std::shared_ptr<TextureSampler>& sampler();
};

}
}
}


#endif // TEXTUREUNITGL_H
