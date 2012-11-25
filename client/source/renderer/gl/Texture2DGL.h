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

	virtual void copy_raw_from_sys_mem()
	{
		this->bind();

	}

};

}
}
}