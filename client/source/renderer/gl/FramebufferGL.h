#include "renderer/Framebuffer.h"

namespace revel
{
namespace renderer
{

class FramebufferGL : public Framebuffer
{
public:
	FramebufferGL()
	{
		::glGenFramebuffers(1, &m_Identifier);
	}	
	
	virtual ~FramebufferGL()
	{
		::glDeleteFramebuffers(1, &m_Identifier);
	}

	void bind()
	{
		::glBindFramebuffer(GL_FRAMEBUFFER, m_Identifier);
	}

	void unbind()
	{
		::glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
};

}	
}