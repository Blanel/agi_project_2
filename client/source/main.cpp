#include <iostream>
#include <vector>

#include "Device.h"
#include "renderer/GraphicsDeviceCreator.h"
#include "renderer/RenderContext.h"
#include "renderer/GraphicsDevice.h"
#include "renderer/ClearState.h"

#include "Image2D.h"
#include "Log.h"
#include "SDL.h"

using namespace revel;
using namespace revel::renderer;


int main(int argc, char *argv[])
{
	R_LOG_INFO("Initializing");

	Device::register_device(renderer::GraphicsDeviceCreator::create_device("OpenGL"));
	auto window = Device::graphics()->create_window(640, 480, "Hello world!");

	auto& ctx = window->context();
	std::cout << sizeof(TGAHeader);

    auto clearstate = std::make_shared<ClearState>();

    clearstate->set_buffers(ClearBuffers::ALL);
    clearstate->set_color(Color4<f32>(0.3f, 0.4f, 0.5f, 1.0f));

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

		window->swap_buffer();
	}

	return 0;
}