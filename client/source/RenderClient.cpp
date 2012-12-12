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

#include "Light.h"

#include "Color.h"
#include "Noise2.h"

#include "Device.h"
#include "Config.h"
#include "Types.h"

#include <string>
#include "SDL.h"

#include "ServerConn.h"

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
#include "Cloud.h"

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

    std::string xmlframe;

	auto& ctx = active_window()->context();

    auto clearstate = std::make_shared<ClearState>();
    clearstate->set_buffers(ClearBuffers::ALL);
    clearstate->set_color(Color4<f32>(0.06, 0.03, 0.02, 1.0));

    auto scenestate = std::make_shared<SceneState>();
    //auto renderstate = std::make_shared<RenderState>();

	auto planemesh = geo::Mesh::create_arrow();
	auto planemeshva = ctx->create_vertex_array(planemesh);
    auto planesp = Device::graphics()->create_shader_program_from_file("../client/source/shaders/plane.vs", 
	    	    												  	   "../client/source/shaders/plane.fs");


    Plane p(planemeshva, planesp, 0.0f, 0.0f);

    auto blur_v_sp = Device::graphics()->create_shader_program_from_file("../client/source/shaders/blur_v.vs", 
												  	    				 "../client/source/shaders/blur_v.fs");

    auto blur_h_sp = Device::graphics()->create_shader_program_from_file("../client/source/shaders/blur_h.vs", 
												  	    				 "../client/source/shaders/blur_h.fs");
	 

	//Create and setup scene
	auto camera = std::make_shared<PerspectiveCamera>();
	
	//ctx->texture_unit(0).set_texture();
	//Only use one (dynamic?) light source
	DirectionalLight sun(vec3(-0.4, -1, 0.3).normalized());

    Scene scene(ctx);
    scene.set_camera(camera);

    Cloud c;
    c.load("e:/cloud4.dae");

    auto tex3d = Device::graphics()->create_texture_3d();

	GameState gs;
	//TerrainManager tm(ctx, 100, 3, 128, 10, 2.5);
	//tm.generate(gs);
	
	Terrain terrain(ctx, 128, 128);

	StopWatch timer;

	camera->set_position(0, 0, 100);

	auto io = std::make_shared<boost::asio::io_service>();
	ClientSocket socket(io);

/*
	Noise2 noise2;

	Image2D<pixel::RGB_u8> heightmap(256, 256);

	for (u32 y = 0; y < 256; ++y)
	{
		for (u32 x = 0; x < 256; ++x)
		{
			f32 n = noise2.noise(x, y) * 128.0f + 128;
			if (n < 0)
				n = 0;
			if (n > 255)
				n = 255;
			heightmap(x, y) = pixel::RGB_u8(n, n, n);
		}
	}


	TGA::write("E:/testimage.tga", heightmap);
*/

	::glEnable(GL_CULL_FACE);

	// CLOUD
	CubeImage ci = CubeImage::generate_fractal_cube(); 

	auto cloud_fb = ctx->create_framebuffer();
	cloud_fb->bind();
	GLuint cloud_rt;
	::glGenTextures(1, &cloud_rt);
	::glBindTexture(GL_TEXTURE_2D, cloud_rt);
	::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_pWindow->width(), m_pWindow->height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, 0); //Empty image
	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	/*
	::glBindTexture(GL_TEXTURE_RECTANGLE, cloud_rt);
	::glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_RGBA, m_pWindow->width(), m_pWindow->height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, 0); //Empty image
	::glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	::glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	*/

	//Depth buffer
	GLuint cloud_depth;
	::glGenRenderbuffers(1, &cloud_depth);
	::glBindRenderbuffer(GL_RENDERBUFFER, cloud_depth);
	::glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_pWindow->width(), m_pWindow->height());
	::glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, cloud_depth);
	
	::glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, cloud_rt, 0);
	GLenum buffers[] = {GL_COLOR_ATTACHMENT0};
	::glDrawBuffers(1, buffers);

	if(::glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		R_LOG_ERR("Invalid framebuffer");

	cloud_fb->unbind();

	try
	{
		socket.open("127.0.0.1", 1234);
	}
	catch(std::exception &e)
	{
		R_LOG_ERR(e.what());
	}

	u32 fps = 0;

	active_window()->show_cursor(false);

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
	        		camera->set_position(0, 0, 120);
	        	break;

	        case SDL_QUIT:
	            m_Running = false;
	        }

    	}

    	//update data
    	//poll socket
    	
    	//auto xmlframe = clientsocket.get_frame_data();
	
		//camera->set_eye(gs.getCentre().first, gs.getCentre().second, 100);
		//doc.save(std::cout);
		//R_LOG_INFO("TS: " << doc.child("tick").attribute("ts").value());

      	//std::cout << xmlframe << std::endl;

      	fps++;

        if (timer.elapsed_time() > 1)
        {
        	R_LOG_INFO("FPS: " << fps);
        	timer.reset();
        	fps = 0;
        }

		//tm.generate(gs);
		
    	//draw data
		ctx->clear(clearstate);

		terrain.draw(ctx, camera);
		p.draw(ctx, camera);

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
		
		// ::glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

		//tmeshva1->bind();
		//sp->use();
		//mvp = Transform::perspective(60.0f, 16.0/9.0, 0.1f, 1000.0f) * Transform::rotate_x(-math::PI/12) * Transform::translate(0, 0, -75);
		//::glDrawElements(GL_TRIANGLES, tmeshva1->index_count(), GL_UNSIGNED_INT, 0);		

		//tm.draw(camera);		

		//mvp = camera->projection_matrix() * (Transform::rotate_z(0.1 * timer.elapsed_time()) * Transform::translate(0, 0, 100)).inversed() * Transform::translate(0, 0, -1*timer.elapsed_time());
		//mvp = camera->projection_matrix() * camera->view_matrix() * Transform::translate(0, 0, 0);		

		// ::glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

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