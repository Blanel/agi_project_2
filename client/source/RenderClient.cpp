#include "RenderClient.h"
#include "renderer/GraphicsDevice.h"
#include "renderer/GraphicsDeviceCreator.h"
#include "renderer/ClearState.h"
#include "renderer/SceneState.h"
#include "renderer/RenderState.h"
#include "renderer/DrawState.h"
#include "renderer/RenderContext.h"
#include "renderer/ShaderProgram.h"
#include "geo/Mesh.h"

#include "Color.h"

#include "Device.h"
#include "Config.h"
#include "Types.h"

#include <string>
#include "SDL.h"

//#include <boost/array.hpp>
//#include <boost/asio.hpp>

#include "Image2D.h"
#include "SimplexNoise.h"

#include "TGA.h"

#include "math/Matrix4x4.h"

using namespace std;
using namespace revel::math;
using namespace revel::renderer;
//using namespace boost::asio;

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

	//TODO: Check boost sockets
	//boost::asio::io_service io_service;
	//boost::asio::ip::tcp::resolver resolver(io_service);
	//resolver::query query()

	auto& ctx = active_window()->context();

    auto clearstate = std::make_shared<ClearState>();
    clearstate->set_buffers(ClearBuffers::ALL);
    clearstate->set_color(Color4<f32>(0.3f, 0.4f, 0.5f, 1.0f));

    auto scenestate = std::make_shared<SceneState>();
    auto renderstate = std::make_shared<RenderState>();
    auto mesh = geo::Mesh::create_cube();
    auto va = ctx->create_vertex_array(mesh);

    // Manually create a mesh
    auto quad = std::make_shared<geo::Mesh>();
    
    auto quadp = quad->create_vertex_attrib<point3>("position");

    quadp->data().push_back(point3(-0.5, -0.5, 0));
    quadp->data().push_back(point3( 0.5, -0.5, 0));
    quadp->data().push_back(point3( 0.5,  0.5, 0));
    quadp->data().push_back(point3(-0.5,  0.5, 0));

    /*
    auto quadn = quad->create_vertex_attrib<vec3>("normal");
    quadn->data().push_back(vec3(0, 0, 1));
    quadn->data().push_back(vec3(0, 0, 1));
    quadn->data().push_back(vec3(0, 0, 1));
    quadn->data().push_back(vec3(0, 0, 1));
    */

    /*
    auto quadt = quad->create_vertex_attrib<vec2>("texcoord");
    quadt->data().push_back(vec2(0, 0));
    quadt->data().push_back(vec2(1, 0));
    quadt->data().push_back(vec2(1, 1));
    quadt->data().push_back(vec2(0, 1));
    */
	

    auto quadi = quad->indices<u32>();
    quadi->data().push_back(0);
    quadi->data().push_back(1);
    quadi->data().push_back(2);

    quadi->data().push_back(0);
    quadi->data().push_back(2);
    quadi->data().push_back(3);

    auto quadva = ctx->create_vertex_array(quad);

    
    //R_LOG_INFO("MESH index count: " << mesh->indices<u32>()->count());
    //R_LOG_INFO("VA index count: " << va->index_count());

    auto sp = Device::graphics()->create_shader_program_from_file("passthrough_vs.glsl", 
    															  "passthrough_fs.glsl"); 
    
    //auto drawstate = std::make_shared<DrawState>(renderstate, sp, va);

    //Create and setup scene
	auto camera = std::make_shared<PerspectiveCamera>();

	//Only use one (dynamic?) light source
	//Light sun(LightType::DIRECTIONAL);
	//sun.set_direction(vec3(0, -1, 0));

	auto& mvp = sp->uniform<mat4>("r_MVP");
	mvp = mat4::Identity;

    Scene scene(ctx);
    scene.set_camera(camera);

    //scene.root().add_child(GeoNode(mesh));

    Image2D<pixel::Gray_f32> heightmap(128, 128);

	f32 factor = 64.0f;

    for (u32 i = 0; i < 128; ++i)
    {
    	for (u32 j = 0; j < 128; ++j)
    	{
			heightmap(i, j) = (SimplexNoise::noise(i / factor, j / factor) + 1.0f) / 2;
    	}
    }

    Image2D<pixel::RGBA_u8> terrain(heightmap);

    TGA::write("D:/hello.tga", terrain);

    //Generate clouds
    //Set render target
    //std::vector<Texture2D> cloud;


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
		//ctx->render(scene);

		quadva->bind();
		::glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    	//va->bind();
    	//::glDrawElements(GL_POINTS, 24, GL_UNSIGNED_INT, 0);

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