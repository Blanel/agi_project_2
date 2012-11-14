#include "RenderWindow.h"
#include "RenderContext.h"

namespace revel
{
namespace renderer
{
	
RenderWindow::RenderWindow(u32 w, u32 h, const std::string& t)	
	: m_Width(w)
	, m_Height(h)
	, m_Title(t)
{}

RenderWindow::~RenderWindow()
{}

const std::shared_ptr<RenderContext>& 
RenderWindow::context() 
{ 
	return m_pContext; 
}

} // ::revel::renderer	
} // ::revel
