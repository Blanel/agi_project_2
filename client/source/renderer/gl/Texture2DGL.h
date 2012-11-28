#include "renderer/Texture2D.h"
#include "SDL.h"

namespace revel
{
namespace renderer
{
namespace gl
{

class Texture2DGL : public Texture2D
{
public:
	Texture2DGL()
		: Texture2D()
	{
		::glGenTextures(1, &m_Identifier);
	}

	virtual ~Texture2DGL()
	{
		::glDeleteTextures(1, &m_Identifier);
	}

	virtual void bind() override
	{
		::glBindTexture(GL_TEXTURE_2D, m_Identifier);
	}

	virtual void unbind() override
	{
		::glBindTexture(GL_TEXTURE_2D, 0);
	}

	virtual void copy_raw_from_sys_mem(void* data, u32 w, u32)
	{
		R_LOG_INFO("Not Yet implemented");
		this->bind();
		//::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, G_RGBA, GL_UN)


	}

};

} // ::revel::texture::gl
} // ::revel::texture
} // ::revel