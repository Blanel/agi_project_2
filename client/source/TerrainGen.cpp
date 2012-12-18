#include "TerrainGen.h"
#include "TerrainTile.h"
#include "geo/Mesh.h"
#include "Noise2.h"
#include "Surface.h"

namespace revel
{


Terrain::Terrain(const std::shared_ptr<renderer::RenderContext>& ctx, i32 tile_w, i32 tile_h)
{
	m_pCtx = ctx;
	m_TileSize = vec2_i32(tile_w, tile_h);

	m_pNoiseGen = std::unique_ptr<SimplexNoise>(new SimplexNoise(2));
	m_pNoiseGen->set_frequency(0.33f/256.0f);
	m_pNoiseGen->set_octaves(8);
	m_pNoiseGen->set_amplitude(15.f);
	m_pNoiseGen->set_persistance(0.335f);

	m_pShaderProgram = Device::graphics()->create_shader_program_from_file("../client/source/shaders/terrain.vs",
																		   "../client/source/shaders/terrain.fs");

	for (i32 j = -8; j < 8; ++j)
		for (i32 i = -8; i < 8; ++i)
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

	// fix edge cases
	std::vector<point3> up(w);
	std::vector<point3> down(w);
	std::vector<point3> left(h);
	std::vector<point3> right(h);

	for (i32 x = 0; x < w; ++x)
	{
		up.push_back(point3(x, h, 1 - fabs(m_pNoiseGen->noise(offset_x + x, offset_y + h))));
		down.push_back(point3(x, -1, 1 - fabs(m_pNoiseGen->noise(offset_x + x, offset_y - 1))));
	}

	for (i32 y = 0; y < h; ++y)
	{
		left.push_back(point3(-1, y, 1 - fabs(m_pNoiseGen->noise(offset_x - 1, offset_y + y))));
		right.push_back(point3(w, y, 1 - fabs(m_pNoiseGen->noise(offset_x + w, offset_y + y))));
	}
	

	//lower
	for (i32 x = 0; x < w; ++x)
	{
		vec3 u, l, r, d;

		if (x == 0)
		{
			u = heightmap(x, 1).pos - heightmap(x, 0).pos;
			l = left[0] - heightmap(x, 0).pos;
			r = heightmap(x+1, 0).pos - heightmap(x, 0).pos;
			d = down[x] - heightmap(x, 0).pos;
		}
		else if (x == w-1)
		{
			u = heightmap(x, 1).pos - heightmap(x, 0).pos;
			l = heightmap(x-1, 0).pos - heightmap(x, 0).pos;
			r = right[0] - heightmap(x, 0).pos;
			d = down[x] - heightmap(x, 0).pos;
		}
		else
		{
			u = heightmap(x, 1).pos - heightmap(x, 0).pos;
			l = heightmap(x-1, 0).pos - heightmap(x, 0).pos;
			r = heightmap(x+1, 0).pos - heightmap(x, 0).pos;
			d = down[x] - heightmap(x, 0).pos;
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
	}	

	//upper
	for (i32 x = 0; x < w; ++x)
	{
		vec3 u, l, r, d;

		if (x == 0)
		{
			u = up[x] - heightmap(x, h-1).pos;
			l = left[h-1] - heightmap(x, h-1).pos;
			r = heightmap(x+1, h-1).pos - heightmap(x, h-1).pos;
			d = heightmap(x, h-2).pos - heightmap(x, h-1).pos;
		}
		else if (x == w-1)
		{
			u = up[x] - heightmap(x, h-1).pos;
			l = heightmap(x-1, h-1).pos - heightmap(x, h-1).pos;
			r = right[h-1] - heightmap(x, h-1).pos;
			d = heightmap(x, h-2).pos - heightmap(x, h-1).pos;
		}
		else
		{
			u = up[x] - heightmap(x, h-1).pos;
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
	}
	
	//left
	for (i32 y = 0; y < h; ++y)
	{
		vec3 u, l, r, d;

		if (y == 0)
		{			
			u = heightmap(0, y+1).pos - heightmap(0, y).pos;
			l = left[y] - heightmap(0, y).pos;
			r = heightmap(1, y).pos - heightmap(0, y).pos;
			d = down[0] - heightmap(0, y).pos;
		}
		else if (y == (h-1))
		{
			u = up[0] - heightmap(0, y).pos;
			l = left[y] - heightmap(0, y).pos;
			r = heightmap(1, y).pos - heightmap(0, y).pos;
			d = heightmap(0, y-1).pos - heightmap(0, y).pos;
		}
		else
		{
			u = heightmap(0, y+1).pos - heightmap(0, y).pos;
			l = left[y] - heightmap(0, y).pos;
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
	}
	
	//right
	for (i32 y = 0; y < h; ++y)
	for (i32 y = 0; y < h; ++y)
	{
		vec3 u, l, r, d;

		if (y == 0)
		{			
			u = heightmap(w-1, y+1).pos - heightmap(w-1, y).pos;
			l = heightmap(w-2, y).pos - heightmap(w-1, y).pos;
			r = right[y] - heightmap(w-1, y).pos;
			d = down[w-1] - heightmap(w-1, y).pos;
		}
		else if (y == (h-1))
		{
			u = up[w-1] - heightmap(w-1, y).pos;
			l = heightmap(w-2, y).pos - heightmap(w-1, y).pos;
			r = right[y] - heightmap(w-1, y).pos;
			d = heightmap(w-1, y-1).pos - heightmap(w-1, y).pos;
		}
		else
		{
			u = heightmap(w-1, y+1).pos - heightmap(w-1, y).pos;
			l = heightmap(w-2, y).pos - heightmap(w-1, y).pos;
			r = right[y] - heightmap(w-1, y).pos;
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

		// normals[y * w + 0] = (uln + urn + lrn + lln)/4;
		heightmap(w-1, y).normal = (uln + urn + lrn + lln)/4; 
	}	

	for (i32 y = 0; y < h; ++y)
	{
		for (i32 x = 0; x < w; ++x)
		{
			meshp->data().push_back(heightmap(x, y).pos);
			meshn->data().push_back(heightmap(x, y).normal);
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


}