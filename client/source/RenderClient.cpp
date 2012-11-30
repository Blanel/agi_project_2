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


#include "Image3D.h"

#include <sstream>

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

i32
RenderClient::run()
{
	m_Running = true;

	//TODO: Check boost sockets
    
    pugi::xml_document doc;    

    std::string xmlframe;

	//ServerConn serverconnection("192.168.0.197");    

	//serverconnection.start();

	std::string ip = Config::get<std::string>("ip");
	u32 port = Config::get<u32>("port");

	boost::asio::io_service io_service;
	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(ip), port);
	boost::asio::ip::tcp::socket socket(io_service);

	auto& ctx = active_window()->context();

    auto clearstate = std::make_shared<ClearState>();
    clearstate->set_buffers(ClearBuffers::ALL);
    clearstate->set_color(Color4<f32>(0.3f, 0.4f, 0.5f, 1.0f));

    auto scenestate = std::make_shared<SceneState>();
    auto renderstate = std::make_shared<RenderState>();
    auto mesh = geo::Mesh::create_cube();
    auto va = ctx->create_vertex_array(mesh);

    // Load assets
    // Manually create a mesh
    //SDL_Surface* image = IMG_Load("E:/ground_grass_1024_tile.jpg");
    //SDL_FreeSurface(image);

    //auto imgtest = Image2D<pixel::RGBA_u8>("E:/ground_grass_1024_tile.jpg");

    //auto text = Device::graphics()->create_texture_2d();



    auto sp = Device::graphics()->create_shader_program_from_file("../client/source/shaders/passthrough_vs.glsl", 
    															  "../client/source/shaders/passthrough_fs.glsl"); 



	auto planemesh = geo::Mesh::create_arrow();
	auto planemeshva = ctx->create_vertex_array(planemesh);

    auto planesp = Device::graphics()->create_shader_program_from_file("../client/source/shaders/plane.vs", 
	    	    												  	   "../client/source/shaders/plane.fs");
    
    //auto drawstate = std::make_shared<DrawState>(renderstate, sp, va);

    //Create and setup scene
	auto camera = std::make_shared<PerspectiveCamera>();

	//ctx->texture_unit(0).set_texture();

	//Only use one (dynamic?) light source
	//Light sun(LightType::DIRECTIONAL);
	//sun.set_direction(vec3(0, -1, 0));

	Image3D<pixel::Gray_f32> image3d(16, 16, 16);

	//auto p = Transform::perspective(60.0f, 16.0/9.0, 0.1f, 1000.0f) * Transform::translate(1, 0, -100) * Transform::rotate_x(math::PI * 2);
	//mvp.set_value();

	auto framebuffer = ctx->create_framebuffer();
	

	//R_LOG_INFO(p);

    Scene scene(ctx);
    scene.set_camera(camera);

    //scene.root().add_child(GeoNode(mesh));

    
    auto tex3d = Device::graphics()->create_texture_3d();


    //auto heightmap 	= Terrain::generate_heightmap(128, 128, 24.0f, 2.5f);
    //auto tmesh 		= Terrain::heightmap_to_mesh(heightmap);


	GameState gs;
	TerrainManager tm(ctx, 100, 3, 128, 10, 2.5);
	tm.generate(gs);
	
	auto tmeshva1  = tm.get_chunk(0,0);

	


    //TGA::write("D:/hello.tga", terrain);

    //Generate clouds
    //Set render target
    //std::vector<Texture2D> cloud;

    // mat4 projection = Transform::perspective(60.0f, 16.0/9.0, 0.1, 1000.0);
    // mat4 viewmatrix = Transform::translate(1, 0, -10);
    // mat4 modelmatrix = mat4::Identity;

	StopWatch timer;

	std::vector<Plane> players;
	players.push_back(Plane(planemeshva, planesp, 0.0f, 0.0f));

	//StopWatch frametimer;

	camera->set_eye(0, 0, 100);

	socket.connect(ep);

	u32 counter = 0;

/*
	while(true)
	{
    	boost::asio::streambuf buffer;
    
      	size_t len = boost::asio::read_until(socket, buffer, "\n");
	      	
      	std::istream is(&buffer);
		std::getline(is, xmlframe);

      	//std::cout << xmlframe << std::endl;
      	counter++;

        if (timer.elapsed_time() > 1)
        {
        	R_LOG_INFO("COUNTER: " << counter);
        }

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

    	boost::asio::streambuf buffer;
    
      	size_t len = boost::asio::read_until(socket, buffer, "\n");

      	
      	std::istream is(&buffer);
		//std::getline(is, xmlframe);

		pugi::xml_parse_result result = doc.load(is);
		R_LOG_INFO("TS: "  << doc.child("tick").attribute("attr").value());



      	//std::cout << xmlframe << std::endl;
      	counter++;

        if (timer.elapsed_time() > 1)
        {
        	R_LOG_INFO("COUNTER: " << counter);
        }

		tm.generate(gs);
		
    	//draw data
		ctx->clear(clearstate);
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
		

		tm.draw(camera);
		



		//mvp = camera->projection_matrix() * (Transform::rotate_z(0.1 * timer.elapsed_time()) * Transform::translate(0, 0, 100)).inversed() * Transform::translate(0, 0, -1*timer.elapsed_time());
		//mvp = camera->projection_matrix() * camera->view_matrix() * Transform::translate(0, 0, 0);

		

		::glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

		for (auto& plane : players)
		{
			//plane.update(...);
			plane.draw(ctx, camera);
		}		

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

void
RenderClient::update()
{

}
	
}