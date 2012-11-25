#include "RenderClient.h"
#include "renderer/GraphicsDevice.h"
#include "renderer/GraphicsDeviceCreator.h"
#include "renderer/ClearState.h"
#include "renderer/SceneState.h"
#include "renderer/RenderState.h"
#include "renderer/DrawState.h"
#include "renderer/RenderContext.h"
#include "geo/Mesh.h"

#include "Color.h"

#include "Device.h"
#include "Config.h"
#include "Types.h"

#include <string>
#include "SDL.h"

using namespace std;
using namespace revel::renderer;

namespace revel
{

RenderClient::RenderClient()
{
	auto api = Config::get<string>("graphics_api");
	u32 screenw = Config::get<u32>("screen_width");
	u32 screenh = Config::get<u32>("screen_height");

	string title = "AGI12 Project 2";

	Device::register_device(renderer::GraphicsDeviceCreator::create_device(api));
	m_pWindow = Device::graphics()->create_window(screenw, screenh, title);

	m_Running = false;
}

RenderClient::~RenderClient()
{

}

bool
RenderClient::is_running() const
{
	return m_Running;
}

i32
RenderClient::run()
{
	m_Running = true;

	auto& ctx = active_window()->context();

    auto clearstate = std::make_shared<ClearState>();
    clearstate->set_buffers(ClearBuffers::ALL);
    clearstate->set_color(Color4<f32>(0.3f, 0.4f, 0.5f, 1.0f));

    auto scenestate = std::make_shared<SceneState>();
    auto renderstate = std::make_shared<RenderState>();
    auto mesh = geo::Mesh::create_cube();
    auto va = ctx->create_vertex_array(mesh);
    
    R_LOG_INFO("MESH index count: " << mesh->indices<u32>()->count());
    R_LOG_INFO("VA index count: " << va->index_count());

    auto sp = Device::graphics()->create_shader_program_from_file("passthrough_vs.glsl", 
    															  "passthrough_fs.glsl"); 
    
    auto drawstate = std::make_shared<DrawState>(renderstate, sp, va);

	while (this->is_running())
	{
		SDL_Event e;

		//Poll events
	    while (SDL_PollEvent(&e))
	    {
	        switch(e.type)
	        {
	        case SDL_MOUSEMOTION:
	            //xrot += e.motion.xrel;
	            //R_LOG_INFO("XROT: " << xrot);
	            break;

	        case SDL_MOUSEBUTTONUP:
	            if (e.button.button == SDL_BUTTON_LEFT)
	            {
	                R_LOG_INFO("MOUSE BUTTON PRESSED: " << "Left");
	                active_window()->show_cursor(true);
	            }
	            if (e.button.button == SDL_BUTTON_RIGHT)
	            {
	                active_window()->show_cursor(false);
	                R_LOG_INFO("MOUSE BUTTON PRESSED: " << "Right");
	            }
	            break;

	        case SDL_KEYDOWN:
	        	if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
	        		m_Running = false;
	        	break;

	        case SDL_QUIT:
	            m_Running = false;
	        }

    	}

    	//update data


    	//draw data
    	ctx->clear(clearstate);

    	va->bind();
    	::glDrawElements(GL_POINTS, 24, GL_UNSIGNED_INT, 0);

    	//ctx->draw(PrimitiveType::TRIANGLES, drawstate, scenestate);

		active_window()->swap_buffer();
		
	}

	return 0;
}

const std::shared_ptr<RenderWindow>&
RenderClient::active_window()
{
	return m_pWindow;
}

void
RenderClient::update()
{

}
	
}