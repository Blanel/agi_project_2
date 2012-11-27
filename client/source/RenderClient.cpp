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

#include "SDL_Image.h"

using namespace std;
using namespace revel::math;
using namespace revel::renderer;
//using namespace boost::asio;

#include "TerrainTile.h"
#include "Plane.h"


#include "Image3D.h"

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

    // Load assets
    // Manually create a mesh
    auto quad = std::make_shared<geo::Mesh>();
    
    auto quadp = quad->create_vertex_attrib<point3>("position");
	auto quadn = quad->create_vertex_attrib<vec3>("normal");
    auto quadt = quad->create_vertex_attrib<vec2>("texcoord");

    quadp->data().push_back(point3(-0.5, -0.5, 0));
    quadp->data().push_back(point3( 0.5, -0.5, 0));
    quadp->data().push_back(point3( 0.5,  0.5, 0));
    quadp->data().push_back(point3(-0.5,  0.5, 0));

    quadn->data().push_back(vec3(0, 0, 1));
    quadn->data().push_back(vec3(0, 0, 1));
    quadn->data().push_back(vec3(0, 0, 1));
    quadn->data().push_back(vec3(0, 0, 1));

    quadt->data().push_back(vec2(0, 0));
    quadt->data().push_back(vec2(1, 0));
    quadt->data().push_back(vec2(1, 1));
    quadt->data().push_back(vec2(0, 1));

    auto quadi = quad->indices<u32>();
    quadi->data().push_back(0);
    quadi->data().push_back(1);
    quadi->data().push_back(2);

    quadi->data().push_back(0);
    quadi->data().push_back(2);
    quadi->data().push_back(3);


    //SDL_Surface* image = IMG_Load("E:/ground_grass_1024_tile.jpg");
    //SDL_FreeSurface(image);

    //auto imgtest = Image2D<pixel::RGBA_u8>("E:/ground_grass_1024_tile.jpg");

    //auto text = Device::graphics()->create_texture_2d();

    auto quadva = ctx->create_vertex_array(quad);

    auto sp = Device::graphics()->create_shader_program_from_file("../client/source/shaders/passthrough_vs.glsl", 
    															  "../client/source/shaders/passthrough_fs.glsl"); 
    
    //auto drawstate = std::make_shared<DrawState>(renderstate, sp, va);

    //Create and setup scene
	auto camera = std::make_shared<PerspectiveCamera>();

	//ctx->texture_unit(0).set_texture();

	//Only use one (dynamic?) light source
	//Light sun(LightType::DIRECTIONAL);
	//sun.set_direction(vec3(0, -1, 0));

	Image3D<pixel::Gray_f32> image3d(16, 16, 16);

	sp->use();
	auto& mvp = sp->uniform<mat4>("r_MVP");
	//auto p = Transform::perspective(60.0f, 16.0/9.0, 0.1f, 1000.0f) * Transform::translate(1, 0, -100) * Transform::rotate_x(math::PI * 2);
	//mvp.set_value();

	auto framebuffer = ctx->create_framebuffer();
	

	//R_LOG_INFO(p);

    Scene scene(ctx);
    scene.set_camera(camera);

    //scene.root().add_child(GeoNode(mesh));


    //auto heightmap 	= Terrain::generate_heightmap(128, 128, 24.0f, 2.5f);
    //auto tmesh 		= Terrain::heightmap_to_mesh(heightmap);
	TerrainTile tt(0,0,128,10, 2.5);
	auto tmesh = tt.mesh;
	auto tmeshva 	= ctx->create_vertex_array(tmesh);

	R_LOG_INFO("MESH: " << tmesh->indices<u32>()->data().size());


    //TGA::write("D:/hello.tga", terrain);

    //Generate clouds
    //Set render target
    //std::vector<Texture2D> cloud;

    // mat4 projection = Transform::perspective(60.0f, 16.0/9.0, 0.1, 1000.0);
    // mat4 viewmatrix = Transform::translate(1, 0, -10);
    // mat4 modelmatrix = mat4::Identity;

	StopWatch timer;

	std::vector<Plane> planes;
	//planes.push_back(Plane());

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
    	//poll socket


    	//draw data
		ctx->clear(clearstate);
		//ctx->render(scene);

		mvp = Transform::perspective(60.0f, 16.0/9.0, 0.1f, 1000.0f) * Transform::rotate_x(-math::PI/6) * Transform::translate(0, 0, -75);

		quadva->bind();
		sp->use();
		::glDrawElements(GL_POINTS, 6, GL_UNSIGNED_INT, 0);
		
		
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

		tmeshva->bind();
		sp->use();
		::glDrawElements(GL_TRIANGLES, tmesh->indices<u32>()->data().size(), GL_UNSIGNED_INT, 0);
		

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