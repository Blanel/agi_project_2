#ifndef RENDERCLIENT_H_
#define RENDERCLIENT_H_

#include "renderer/RenderWindow.h"
#include "Scene.h"
#include <memory>
#include "FrameParser.h"
//#include <boost/asio.hpp>
#include "ServerConn.h"

namespace revel
{

class RenderClient
{
	std::shared_ptr<renderer::RenderWindow> m_pWindow;
	void gs_update_loop();
	bool m_Running;
	bool m_Connected;
	FrameParser m_fp;
	GameState m_gs;
	std::shared_ptr<ClientSocket> m_socket;

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