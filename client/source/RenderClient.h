#include "renderer/RenderWindow.h"
#include "Scene.h"
#include <memory>

namespace revel
{

class RenderClient
{
	std::shared_ptr<renderer::RenderWindow> m_pWindow;
	bool m_Running;

	std::shared_ptr<Scene> m_pScene;

	void update();

public:
	RenderClient();	
	~RenderClient();

	i32 run();

	bool is_running() const;
	const std::shared_ptr<renderer::RenderWindow>& active_window();
	
};


}