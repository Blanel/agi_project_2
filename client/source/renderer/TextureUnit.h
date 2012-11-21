#ifndef TEXTUREUNIT_H
#define TEXTUREUNIT_H

#include "renderer/Texture2D.h"
#include "renderer/TextureSampler.h"

#include <memory>

namespace revel
{
namespace renderer
{

class TextureUnit
{
protected:
    std::shared_ptr<Texture2D> m_pTexture;
    std::shared_ptr<TextureSampler> m_pSampler;

public:
    TextureUnit() {}
    virtual ~TextureUnit() {}
    virtual void set_texture(const std::shared_ptr<Texture2D>& tex) = 0;
    virtual void set_sampler(const std::shared_ptr<TextureSampler>& sampler) = 0;
	const std::shared_ptr<Texture2D>& texture() = 0;
	const std::shared_ptr<TextureSampler>& sampler() = 0;
};

}
}


#endif // TEXTUREUNIT_H
