#ifndef RENDERCLIENT_H_
#define RENDERCLIENT_H_

#include "renderer/RenderWindow.h"
#include "Scene.h"
#include <memory>
//#include <boost/asio.hpp>

namespace revel
{

class RenderClient
{
	std::shared_ptr<renderer::RenderWindow> m_pWindow;
	bool m_Running;
	bool m_Connected;

public:
	RenderClient();	
	~RenderClient();

	i32 connect(const std::string& ip);
	i32 run();

	bool is_running() const;
	bool is_connected() const;
	const std::shared_ptr<renderer::RenderWindow>& active_window();
	
};

} // ::revel

#endif // RENDERCLIENT_H_