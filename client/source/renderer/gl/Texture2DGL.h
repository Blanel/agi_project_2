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
	{
		::glGenTextures(1, &m_Identifier);
	}

	virtual ~Texture2DGL()
	{
		::glDeleteTextures(1, &m_Identifier);
	}

	virtual void bind()
	{
		::glBindTexture(GL_TEXTURE_2D, m_Identifier);
	}

	virtual void unbind()
	{
		::glBindTexture(GL_TEXTURE_2D, 0);
	}


};

}
}
}