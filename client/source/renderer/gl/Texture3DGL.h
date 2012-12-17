#ifndef TEXTURE3DGL_H_
#define TEXTURE3DGL_H_

#include "renderer/Texture3D.h"

namespace revel
{
namespace renderer
{
namespace gl
{
	
class Texture3DGL : public Texture3D
{

public:
	Texture3DGL()
	{
		::glGenTextures(1, &m_Identifier);
	}

	virtual ~Texture3DGL()
	{
		::glDeleteTextures(1, &m_Identifier);
	}

	void bind()
	{
		::glBindTexture(GL_TEXTURE_3D, m_Identifier);
	}

	void unbind()
	{
		::glBindTexture(GL_TEXTURE_3D, 0);
	}
};


} // ::revel::renderer::gl
} // ::revel::renderer
} // ::revel

#endif // TEXTURE3DGL_H_