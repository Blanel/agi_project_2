#include <iostream>
#include <vector>

#include "Device.h"
#include "Config.h"
#include "Log.h"

#include "SDL.h"
#include "Image2D.h"

#include "geo/Mesh.h"
#include "renderer/GraphicsDeviceCreator.h"
#include "renderer/RenderContext.h"
#include "renderer/GraphicsDevice.h"
#include "renderer/ClearState.h"
#include "renderer/SceneState.h"
#include "renderer/RenderState.h"
#include "renderer/DrawState.h"
#include "renderer/ShaderProgram.h"

#include "BoundingVolume.h"

using namespace std;
using namespace revel;
using namespace revel::renderer;


int main(int argc, char *argv[])
{
	R_LOG_INFO("Initializing");

	auto api = Config::get<string>("graphics_api");
	u32 screenw = Config::get<u32>("screen_width");
	u32 screenh = Config::get<u32>("screen_height");
	string title = "AGI12 Project 2";

	Device::register_device(renderer::GraphicsDeviceCreator::create_device(api));
	auto window = Device::graphics()->create_window(screenw, screenh, title);
	auto& ctx = window->context();

    auto clearstate = std::make_shared<ClearState>();
    clearstate->set_buffers(ClearBuffers::ALL);
    clearstate->set_color(Color4<f32>(0.3f, 0.4f, 0.5f, 1.0f));

    auto scenestate = std::make_shared<SceneState>();
    auto renderstate = std::make_shared<RenderState>();
    auto mesh = geo::Mesh::create_cube();
    auto va = ctx->create_vertex_array(mesh);
    

    auto sp = Device::graphics()->create_shader_program_from_file("passthrough_vs.glsl", 
    															  "passthrough_fs.glsl"); 
    
    
    //auto vbo = 

    //R_LOG_INFO("Creating a draw state");

    auto drawstate = std::make_shared<DrawState>(renderstate, sp, va);

    //R_LOG_INFO("Crash");

	bool running = true;

	while (running)
	{
		ctx->clear(clearstate);

	    SDL_Event e;

	    //u8 currentMouseState = SDL_GetMouseState(NULL, NULL);

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
	                window->show_cursor(true);
	            }
	            if (e.button.button == SDL_BUTTON_RIGHT)
	            {
	                window->show_cursor(false);
	                R_LOG_INFO("MOUSE BUTTON PRESSED: " << "Right");
	            }
	            break;

	        case SDL_QUIT:
	            running = false;
	        }

    	}

    	//ctx->draw(PrimitiveType::TRIANGLES, drawstate, scenestate);

		window->swap_buffer();
	}

	return 0;
}