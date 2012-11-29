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

	virtual void copy_raw_from_sys_mem(void* data, u32 w, u32 h)
	{
		//R_LOG_INFO("Not Yet implemented");
		this->bind();
		
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    	
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    	
		
		::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);		
		this->unbind();
	}

};

} // ::revel::texture::gl
} // ::revel::texture
} // ::revel