#include "TerrainGen.h"
#include "TerrainTile.h"
#include "geo/Mesh.h"
#include "Noise2.h"
#include "Surface.h"
#include "Image2D.h"

namespace revel
{


Terrain::Terrain(const std::shared_ptr<renderer::RenderContext>& ctx, i32 tile_w, i32 tile_h)
{
	m_pCtx = ctx;
	m_TileSize = vec2_i32(tile_w, tile_h);

	m_pNoiseGen = std::unique_ptr<SimplexNoise>(new SimplexNoise(2));
	m_pNoiseGen->set_frequency(0.32f/256.0f);
	m_pNoiseGen->set_octaves(12);
	m_pNoiseGen->set_amplitude(17.5f);
	m_pNoiseGen->set_persistance(0.39f);

	m_pShaderProgram = Device::graphics()->create_shader_program_from_file("../client/source/shaders/terrain.vs",
																		   "../client/source/shaders/terrain.fs");

	// Image2D<pixel::RGB_u8> img("e:/rock.tga");

	// m_DiffuseMap = Device::graphics()->create_texture_2d();
	// m_DiffuseMap->copy_from_sys_mem(img);	 

	for (i32 j = -3; j < 4; ++j)
		for (i32 i = -3; i < 4; ++i)
			create_tile(i, j);
}

Terrain::~Terrain()
{

}

void
Terrain::create_tile(i32 tile_x, i32 tile_y)
{
	const u32 w = m_TileSize.x;
	const u32 h = m_TileSize.y;

	Surface<TerrainVertex> heightmap(w, h);

	auto mesh = std::make_shared<geo::Mesh>();    
    auto meshp = mesh->create_vertex_attrib<point3>("position");
    auto meshn = mesh->create_vertex_attrib<vec3>("normals");
    auto mesht = mesh->create_vertex_attrib<vec2>("uv0");
    auto meshi = mesh->indices<u32>();
	

    i32 offset_x = tile_x * (m_TileSize.x - 1);
    i32 offset_y = tile_y * (m_TileSize.y - 1);

    for(i32 y=0; y<h ; y++)
	{
		for(i32 x=0 ; x<w ; x++)
		{
			f32 n = 1 - fabs(m_pNoiseGen->noise(offset_x + x, offset_y + y));
			heightmap(x, y).pos = point3(x, y, n);
			heightmap(x, y).uv = vec2(4*x/w, 4*y/h);
		}
	}

	//Triangulate mesh
	for(i32 y = 0; y < h-1 ; y++)
	{
		for(i32 x = 0; x < w-1 ; x++)
		{
			meshi->add_triangle((y)*w+x, (y)*w+(x+1), (y+1)*w+(x+1));
    		meshi->add_triangle((y+1)*w+(x+1), (y+1)*w+x, (y)*w+x);
		}		
	}

		//TODO: storing half of the normals would suffice
	for (i32 y = 1; y < h-1; ++y)
	{
		for (i32 x = 1; x < w-1; ++x)
		{
			//upper left
			vec3 d = heightmap(x, y - 1).pos - heightmap(x, y).pos;
			vec3 l = heightmap(x - 1, y).pos - heightmap(x, y).pos;
			vec3 r = heightmap(x + 1, y).pos - heightmap(x, y).pos;
			vec3 u = heightmap(x, y + 1).pos - heightmap(x, y).pos;

			math::normalize(u);
			math::normalize(d);
			math::normalize(l);
			math::normalize(r);

			vec3 uln = math::cross(u, l);
			vec3 urn = math::cross(r, u);
			vec3 lrn = math::cross(d, r);
			vec3 lln = math::cross(l, d);

			heightmap(x, y).normal = (uln + urn + lrn + lln)/4;
		}
	}

	//lower
	for (i32 x = 0; x < w; ++x)
	{
		vec3 u, l, r, d;

		if (x == 0)
		{
			u = heightmap(x, 1).pos - heightmap(x, 0).pos;
			l = point3(x-1, 0, 1 - fabs(m_pNoiseGen->noise(offset_x + x-1, offset_y + 0))) - heightmap(x, 0).pos;
			r = heightmap(x+1, 0).pos - heightmap(x, 0).pos;
			d = point3(x, -1, 1 - fabs(m_pNoiseGen->noise(offset_x + x, offset_y - 1))) - heightmap(x, 0).pos;
		}
		else if (x == w-1)
		{
			u = heightmap(x, 1).pos - heightmap(x, 0).pos;
			l = heightmap(x-1, 0).pos - heightmap(x, 0).pos;
			r = point3(x+1, 0, 1 - fabs(m_pNoiseGen->noise(offset_x + x+1, offset_y))) - heightmap(x, 0).pos;
			d = point3(x, -1, 1 - fabs(m_pNoiseGen->noise(offset_x + x, offset_y - 1))) - heightmap(x, 0).pos;
		}
		else
		{
			u = heightmap(x, 1).pos - heightmap(x, 0).pos;
			l = heightmap(x-1, 0).pos - heightmap(x, 0).pos;
			r = heightmap(x+1, 0).pos - heightmap(x, 0).pos;
			d = point3(x, -1, 1 - fabs(m_pNoiseGen->noise(offset_x + x, offset_y - 1))) - heightmap(x, 0).pos;
		}

		math::normalize(u);
		math::normalize(d);
		math::normalize(l);
		math::normalize(r);

		vec3 uln = math::cross(u, l);
		vec3 urn = math::cross(r, u);
		vec3 lrn = math::cross(d, r);
		vec3 lln = math::cross(l, d);

		//normals[0 * w + x] = (uln + urn + lrn + lln)/4;
		heightmap(x, 0).normal = (uln + urn + lrn + lln)/4;
		// heightmap(x, 0).normal = vec3::UnitZ;
	}	

	//upper
	for (i32 x = 0; x < w; ++x)
	{
		vec3 u, l, r, d;

		if (x == 0)
		{
			u = point3(x, h, 1 - fabs(m_pNoiseGen->noise(offset_x + x, offset_y + h))) - heightmap(x, h-1).pos;
			l = point3(x-1, h-1, 1 - fabs(m_pNoiseGen->noise(offset_x + x-1, offset_y + (h-1)))) - heightmap(x, h-1).pos;
			r = heightmap(x+1, h-1).pos - heightmap(x, h-1).pos;
			d = heightmap(x, h-2).pos - heightmap(x, h-1).pos;
		}
		else if (x == w-1)
		{
			u = point3(x, h, 1 - fabs(m_pNoiseGen->noise(offset_x + x, offset_y + h))) - heightmap(x, h-1).pos;
			l = heightmap(x-1, h-1).pos - heightmap(x, h-1).pos;
			r = point3(x+1, h-1, 1 - fabs(m_pNoiseGen->noise(offset_x + x+1, offset_y + (h-1)))) - heightmap(x, h-1).pos;
			d = heightmap(x, h-2).pos - heightmap(x, h-1).pos;
		}
		else
		{
			u = point3(x, h, 1 - fabs(m_pNoiseGen->noise(offset_x + x, offset_y + h))) - heightmap(x, h-1).pos;
			l = heightmap(x-1, h-1).pos - heightmap(x, h-1).pos;
			r = heightmap(x+1, h-1).pos - heightmap(x, h-1).pos;
			d = heightmap(x, h-2).pos - heightmap(x, h-1).pos;
		}

		math::normalize(u);
		math::normalize(d);
		math::normalize(l);
		math::normalize(r);

		vec3 uln = math::cross(u, l);
		vec3 urn = math::cross(r, u);
		vec3 lrn = math::cross(d, r);
		vec3 lln = math::cross(l, d);

		// normals[h-1 * w + x] = (uln + urn + lrn + lln)/4;
	 	heightmap(x, h-1).normal = (uln + urn + lrn + lln)/4; 
	 	// heightmap(x, h-1).normal = vec3::UnitZ;
	}
	
	//left
	for (i32 y = 0; y < h; ++y)
	{
		vec3 u, l, r, d;

		if (y == 0)
		{			
			u = heightmap(0, y+1).pos - heightmap(0, y).pos;
			l = point3(-1, y, 1 - fabs(m_pNoiseGen->noise(offset_x - 1, offset_y + y))) - heightmap(0, y).pos;
			r = heightmap(1, y).pos - heightmap(0, y).pos;
			d = point3(0, y-1, 1 - fabs(m_pNoiseGen->noise(offset_x + 0, offset_y + (y-1)))) - heightmap(0, y).pos;
		}
		else if (y == (h-1))
		{
			u = point3(0, y+1, 1 - fabs(m_pNoiseGen->noise(offset_x + 0, offset_y + y+1))) - heightmap(0, y).pos;
			l = point3(-1, y, 1 - fabs(m_pNoiseGen->noise(offset_x - 1, offset_y + y))) - heightmap(0, y).pos;
			r = heightmap(1, y).pos - heightmap(0, y).pos;
			d = heightmap(0, y-1).pos - heightmap(0, y).pos;
		}
		else
		{
			u = heightmap(0, y+1).pos - heightmap(0, y).pos;
			l = point3(-1, y, 1 - fabs(m_pNoiseGen->noise(offset_x - 1, offset_y + y))) - heightmap(0, y).pos;
			r = heightmap(1, y).pos - heightmap(0, y).pos;
			d = heightmap(0, y-1).pos - heightmap(0, y).pos;
		}

		math::normalize(u);
		math::normalize(d);
		math::normalize(l);
		math::normalize(r);

		vec3 uln = math::cross(u, l);
		vec3 urn = math::cross(r, u);
		vec3 lrn = math::cross(d, r);
		vec3 lln = math::cross(l, d);

		// normals[y * w + 0] = (uln + urn + lrn + lln)/4;
		heightmap(0, y).normal = (uln + urn + lrn + lln)/4; 
		// heightmap(0, y).normal = vec3::UnitZ;
	}
	
	//right
	for (i32 y = 0; y < h; ++y)
	{
		vec3 u, l, r, d;

		if (y == 0)
		{			
			u = heightmap(w-1, y+1).pos - heightmap(w-1, y).pos;
			l = heightmap(w-2, y).pos - heightmap(w-1, y).pos;
			r = point3(w, y, 1 - fabs(m_pNoiseGen->noise(offset_x + w, offset_y + y))) - heightmap(0, y).pos; - heightmap(w-1, y).pos;
			d = point3(w-1, y-1, 1 - fabs(m_pNoiseGen->noise(offset_x + w-1, offset_y - 1))) - heightmap(w-1, y).pos;
		}
		else if (y == (h-1))
		{
			u = point3(w-1, y+1, 1 - fabs(m_pNoiseGen->noise(offset_x + w-1, offset_y + y+1))) - heightmap(w-1, y).pos;
			l = heightmap(w-2, y).pos - heightmap(w-1, y).pos;
			r = point3(w, y, 1 - fabs(m_pNoiseGen->noise(offset_x + w, offset_y + y))) - heightmap(0, y).pos; - heightmap(w-1, y).pos;
			d = heightmap(w-1, y-1).pos - heightmap(w-1, y).pos;
		}
		else
		{
			u = heightmap(w-1, y+1).pos - heightmap(w-1, y).pos;
			l = heightmap(w-2, y).pos - heightmap(w-1, y).pos;
			r = point3(w, y, 1 - fabs(m_pNoiseGen->noise(offset_x + w, offset_y + y))) - heightmap(0, y).pos; - heightmap(w-1, y).pos;
			d = heightmap(w-1, y-1).pos - heightmap(w-1, y).pos;
		}

		math::normalize(u);
		math::normalize(d);
		math::normalize(l);
		math::normalize(r);

		vec3 uln = math::cross(u, l);
		vec3 urn = math::cross(r, u);
		vec3 lrn = math::cross(d, r);
		vec3 lln = math::cross(l, d);

		heightmap(w-1, y).normal = (uln + urn + lrn + lln)/4; 
		// heightmap(w-1, y).normal = vec3::UnitZ; 
	}	

	for (i32 y = 0; y < h; ++y)
	{
		for (i32 x = 0; x < w; ++x)
		{
			meshp->data().push_back(heightmap(x, y).pos);
			meshn->data().push_back(heightmap(x, y).normal);
			mesht->data().push_back(heightmap(x, y).uv);
		}
	}

	auto tile = std::make_shared<TerrainTile>();

	auto va = m_pCtx->create_vertex_array(mesh);
	tile->set_vertex_array(va);

	m_Tiles.insert(std::make_pair(ivec2(tile_x, tile_y), tile));

}

void 
Terrain::draw(const std::shared_ptr<renderer::RenderContext>& ctx, const std::shared_ptr<Camera>& cam)
{
	//::glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	::glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	m_pShaderProgram->use();		
	//m_pDiffuseMap->bind();
	
	auto& mvp = m_pShaderProgram->uniform<math::mat4>("r_MVP");
	auto& mv= m_pShaderProgram->uniform<math::mat4>("r_ModelView");

	for (auto iter = m_Tiles.begin(); iter != m_Tiles.end(); ++iter)
	{
		if (!iter->second)
			continue;

		f32 x = cam->position().x / (m_TileSize.x - 1);
		f32 y = cam->position().y / (m_TileSize.y - 1);

		if (fabs(iter->first.x - x) > 3 || fabs(iter->first.y - y) > 3)
			continue;

		mvp = cam->projection_matrix() * cam->view_matrix() * math::Transform::translate(iter->first.x * (m_TileSize.x - 1), iter->first.y * (m_TileSize.y - 1), 0);
		mv = cam->view_matrix() * math::Transform::translate(iter->first.x * (m_TileSize.x - 1), iter->first.y * (m_TileSize.y - 1), 0);

		auto& va = iter->second->vertex_array();
		va->bind();
		::glDrawElements(GL_TRIANGLES, va->index_count(), GL_UNSIGNED_INT, 0);
		va->unbind();
	}
}

const std::shared_ptr<TerrainTile>&
Terrain::tile(const vec2_i32& p)
{
	return m_Tiles[p];
}

void 
Terrain::update(const GameState& gs)
{
	//step through all tiles, if tile > set distance, remove from map

}

void
Terrain::update(const std::shared_ptr<Camera>& cam)
{
	i32 x = cam->position().x / (m_TileSize.x - 1);
	i32 y = cam->position().y / (m_TileSize.y - 1);

	for (i32 ty = y-4; ty < y+4; ++ty)
	{
		for (i32 tx = x-4; tx < x+4; ++tx)
		{
			if (m_Tiles.find(ivec2(tx, ty)) == m_Tiles.end())
				create_tile(tx, ty);

		}
	}
}


}