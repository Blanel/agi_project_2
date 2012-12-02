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

//#include "ServerConn.h"

#include "Image2D.h"
#include "SimplexNoise.h"

#include "TGA.h"

#include "math/Matrix4x4.h"

#include "SDL_Image.h"

using namespace std;
using namespace revel::math;
using namespace revel::renderer;
//using namespace boost::asio;

#include "TerrainTile.h"
#include "TerrainManager.h"
#include "Plane.h"

#include <pugixml.hpp>
#include <thread>

#include "TerrainGen.h"

#include "Image3D.h"

#include <sstream>

#include "PerlinNoise.h"

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
	m_Connected = false;

	::glEnable(GL_TEXTURE_2D);
}

RenderClient::~RenderClient()
{

}

bool
RenderClient::is_running() const
{
	return m_Running;
}

bool
RenderClient::is_connected() const
{
	return m_Connected;
}

i32
RenderClient::run()
{
	m_Running = true;

	std::string ip = Config::get<std::string>("ip");
	u32 port = Config::get<u32>("port");

    pugi::xml_document doc;    
    std::string xmlframe;

	auto& ctx = active_window()->context();

    auto clearstate = std::make_shared<ClearState>();
    clearstate->set_buffers(ClearBuffers::ALL);
    clearstate->set_color(Color4<f32>(0.3f, 0.4f, 0.5f, 1.0f));

    auto scenestate = std::make_shared<SceneState>();
    //auto renderstate = std::make_shared<RenderState>();

	auto planemesh = geo::Mesh::create_arrow();
	auto planemeshva = ctx->create_vertex_array(planemesh);
    auto planesp = Device::graphics()->create_shader_program_from_file("../client/source/shaders/plane.vs", 
	    	    												  	   "../client/source/shaders/plane.fs");
    //Create and setup scene
	auto camera = std::make_shared<PerspectiveCamera>();

	//ctx->texture_unit(0).set_texture();

	//Only use one (dynamic?) light source
	//Light sun(LightType::DIRECTIONAL);
	//sun.set_direction(vec3(0, -1, 0));

	Image3D<pixel::Gray_f32> image3d(16, 16, 16);

	/*
	PerlinNoise perlin(0x4711);

	Image2D<pixel::Gray_f32> pi(256, 256);

	for (u32 y = 0; y < 256; ++y)
	{
		for (u32 x = 0; x < 256; ++x)
		{
			pi(x, y).val = perlin.noise(x, y, 0.5);
			pi(x, y).val = (pi(x, y).val + 1.0f)/2.0f;
		}
	}
	*/

	SimplexNoise simplex(0x4711);
	simplex.set_amplitude(1.0f);
	simplex.set_frequency(4.0f / 256.0f);
	simplex.set_octaves(1);
	//simplex.set_persistance(.5f);

	Image2D<pixel::Gray_f32> pi(256, 256);

	for (u32 y = 0; y < 256; ++y)
	{
		for (u32 x = 0; x < 256; ++x)
		{
			pi(x, y).val = simplex.noise(x, y);
			//pi(x, y).val = (pi(x, y).val + 1.0f)/2.0f;
		}
	}


	Image2D<pixel::RGBA_u8> heightmap(pi);

	TGA::write("e:/heightmap.tga", heightmap);

	auto framebuffer = ctx->create_framebuffer();
	
    Scene scene(ctx);
    scene.set_camera(camera);

    auto tex3d = Device::graphics()->create_texture_3d();

	GameState gs;
	//TerrainManager tm(ctx, 100, 3, 128, 10, 2.5);
	//tm.generate(gs);
	
	//auto tmeshva1  = tm.get_chunk(0,0);

    //TGA::write("D:/hello.tga", terrain);
    //Generate clouds
    //Set render target
    //std::vector<Texture2D> cloud;

	Terrain terrain(ctx);

	StopWatch timer;

	camera->set_eye(0, 0, 100);

	//ServerConn serverconn(ip, port);

	/*
	if (!ip.empty())
	{
		serverconn.start();
	}
	*/
	


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
	        	else if (e.key.keysym.scancode == SDL_SCANCODE_A);
	        		camera->set_eye(0, 0, 120);
	        	break;

	        case SDL_QUIT:
	            m_Running = false;
	        }

    	}
    	//update data
    	//poll socket

    	
    	/*
    	boost::asio::streambuf buffer;  
      	size_t len = boost::asio::read_until(socket, buffer, "\n");
      	std::istream is(&buffer);
		std::getline(is, xmlframe);


		pugi::xml_parse_result result = doc.load(is);
		*/

		/*		
		auto planes = doc.child("tick").child("planes");

		for (auto p = planes.child("p"); p; p = p.next_sibling("p"))
		{
			auto id = p.attribute("id").as_int();
			f32 x = p.child("x").text().as_double();
			f32 y = p.child("y").text().as_double();
			f32 a = p.child("a").text().as_double();
			i32 status = p.child("status").text().as_int();

			if (status == 1)
			{
				gs.get_planes().push_back(AirPlane());
				gs.get_planes().back().x = x;
				gs.get_planes().back().y = y;
				gs.get_planes().back().angle = a;
			}
			else
			{
				gs.get_planes()[id].x = x;
				gs.get_planes()[id].y = y;
				gs.get_planes()[id].angle = a;
			}
		}
		*/
		

		//camera->set_eye(gs.getCentre().first, gs.getCentre().second, 100);
		//doc.save(std::cout);
		//R_LOG_INFO("TS: " << doc.child("tick").attribute("ts").value());

      	//std::cout << xmlframe << std::endl;

      	/*
      	counter++;

        if (timer.elapsed_time() > 1)
        {
        	R_LOG_INFO("COUNTER: " << counter);
        }
        */

		//tm.generate(gs);
		
    	//draw data
		ctx->clear(clearstate);

		terrain.draw(ctx, camera);

		//draw gamestate
		/*
		{

			planemeshva->bind();
			planesp->use();

			for (auto& plane : gs.get_planes())
			{

				::glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

				math::mat4 model = Transform::translate(plane.x, plane.y, 50) * Transform::rotate_y(plane.angle);
				math::mat4 view = camera->view_matrix();
				math::mat4 projection = camera->projection_matrix();

				auto& color = planesp->uniform<vec3>("r_Color");
				color = vec3(0.4, 0.6, 0.9);
			
				R_LOG_INFO("Plane pos: " << plane.x << ", " << plane.y);

				auto& mvp = planesp->uniform<mat4>("r_MVP");

				mvp = projection * view * model;

				::glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			}

			planemeshva->unbind();	
		}
		*/
		//ctx->render(scene);

		/*
		player_mvp = Transform::perspective(60.0f, 16.0/9.0, 0.1f, 1000.0f) * Transform::rotate_x(0) * Transform::translate(0, 0, -75);

		::glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		quadva->bind();
		player_sp->use();
		::glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		*/
		
		::glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

		//tmeshva1->bind();
		//sp->use();
		//mvp = Transform::perspective(60.0f, 16.0/9.0, 0.1f, 1000.0f) * Transform::rotate_x(-math::PI/12) * Transform::translate(0, 0, -75);
		//::glDrawElements(GL_TRIANGLES, tmeshva1->index_count(), GL_UNSIGNED_INT, 0);		

		//tm.draw(camera);		

		//mvp = camera->projection_matrix() * (Transform::rotate_z(0.1 * timer.elapsed_time()) * Transform::translate(0, 0, 100)).inversed() * Transform::translate(0, 0, -1*timer.elapsed_time());
		//mvp = camera->projection_matrix() * camera->view_matrix() * Transform::translate(0, 0, 0);		

		::glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

/*
		for (auto& plane : players)
		{
			//plane.update(...);
			plane.draw(ctx, camera);
		}		
*/

		//::glDrawElements(GL_POINTS, tmeshp->data().size(), GL_UNSIGNED_INT, 0);
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

	
}