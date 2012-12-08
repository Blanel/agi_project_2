#include "TerrainGen.h"
#include "geo/Mesh.h"

namespace revel
{

TerrainTile::TerrainTile()
{

}

void 
TerrainTile::set_vertex_array(const std::shared_ptr<renderer::VertexArray>& va)
{
	m_pVertexArray = va;
}

const std::shared_ptr<renderer::VertexArray>& 
TerrainTile::vertex_array()
{
	return  m_pVertexArray;
}


Terrain::Terrain(const std::shared_ptr<renderer::RenderContext>& ctx, u32 tile_w, u32 tile_h)
{
	m_pCtx = ctx;
	m_TileSize = vec2_u32(tile_w, tile_h);

	m_pNoiseGen = std::unique_ptr<SimplexNoise>(new SimplexNoise());
	m_pNoiseGen->set_frequency(2.0f/128.0f);
	m_pNoiseGen->set_octaves(6);
	m_pNoiseGen->set_amplitude(2.5f);
	m_pNoiseGen->set_persistance(0.2f);

	m_pShaderProgram = Device::graphics()->create_shader_program_from_file("../client/source/shaders/terrain.vs",
																		   "../client/source/shaders/terrain.fs");

	create_tile(vec2_i32(0,0));
	create_tile(vec2_i32(-1,0));
	create_tile(vec2_i32(0,-1));
	create_tile(vec2_i32(-1,-1));

	m_DrawNormals = true;
}

Terrain::~Terrain()
{

}

void
Terrain::create_tile(i32 x, i32 y)
{
	create_tile(vec2_i32(x, y));
}

void
Terrain::create_tile(const vec2_i32& p)
{
	u32 w, h;
	w = h = 128;

	std::unique_ptr<TerrainTile> tile(new TerrainTile());

	auto mesh = std::make_shared<geo::Mesh>();    
    auto meshp = mesh->create_vertex_attrib<point3>("position");
    auto meshn = mesh->create_vertex_attrib<vec3>("normals");
    auto mesht = mesh->create_vertex_attrib<vec2>("uv0");
    auto meshi = mesh->indices<u32>();

    Image2D<pixel::Gray_f32> hmap(w, h);

	for(int y=0; y<h ; y++)
	{
		for(int x=0 ; x<w ; x++)
		{
			f32 n = (m_pNoiseGen->noise(p.x * 128 + x, p.y * 128 + y));

			hmap(x, y).val = n;
			meshp->data().push_back(point3(x,y,n));
			mesht->data().push_back(vec2(x / (128.0f / 16), y / (128.0f / 16)));
		}
	}

	for(int y = 0; y < h-1 ; y++)
	{
		for(int x = 0; x < w-1 ; x++)
		{
			meshi->add_triangle((y+1)*w+x, (y+1)*w+(x+1), y*w+(x+1));
    		meshi->add_triangle(y*w+(x+1), y*w+x, (y+1)*w+x);
		}		
	}


	std::vector<vec3> normals(128 * 128, vec3::UnitZ);


	//TODO: storing half of the normals would suffice
	for (i32 y = 1; y < 128-1; ++y)
	{
		for (i32 x = 1; x < 128-1; ++x)
		{
			//upper left

			vec3 u = point3(x, y+1, hmap(x, y+1).val) - point3(x, y, hmap(x, y).val);
			vec3 l = point3(x-1, y, hmap(x-1, y).val) - point3(x, y, hmap(x, y).val);
			vec3 r = point3(x+1, y, hmap(x+1, y).val) - point3(x, y, hmap(x, y).val);
			vec3 d = point3(x, y-1, hmap(x, y-1).val) - point3(x, y, hmap(x, y).val);

			vec3 uln = math::cross(math::normalize(u), math::normalize(l));
			vec3 urn = math::cross(math::normalize(r), math::normalize(u));
			vec3 lrn = math::cross(math::normalize(d), math::normalize(r));
			vec3 lln = math::cross(math::normalize(l), math::normalize(d));

			math::normalize(uln);
			math::normalize(urn);
			math::normalize(lrn);
			math::normalize(lln);

			normals[y * (128) + x] = (uln + urn + lrn + lln)/4;
		}
	}

	//fix edge cases
	std::vector<point3> up(128);
	std::vector<point3> down(128);
	std::vector<point3> left(128);
	std::vector<point3> right(128);

	for (i32 i = 0; i < 128+1; ++i)
	{
		up.push_back(point3(i,0-1,m_pNoiseGen->noise(i,-1)));
		down.push_back(point3(i, 128+1, m_pNoiseGen->noise(i,128+1)));
		left.push_back(point3(0-1, i, m_pNoiseGen->noise(0-1, i)));
		right.push_back(point3(128+1, i, m_pNoiseGen->noise(128+1, i)));
	}

	//upper
	for (i32 x = 0; x < 128; ++x)
	{
		vec3 u, l, r, d;

		if (x == 0)
		{
			u = up[x];
			l = left[x];
			r = normals[0 * 128 + (x+1)];
			d = normals[1 * 128 + (x)];
		}
		else if (x == 127)
		{
			u = up[x];
			l = normals[0 * 128 + (x-1)];
			r = right[x];
			d = normals[1 * 128 + (x)];
		}
		else
		{
			u = up[x];
			l = normals[0 * 128 + (x-1)];
			r = normals[0 * 128 + (x+1)];
			d = normals[1 * 128 + (x)];
		}

		vec3 uln = math::cross(math::normalize(u), math::normalize(l));
		vec3 urn = math::cross(math::normalize(r), math::normalize(u));
		vec3 lrn = math::cross(math::normalize(d), math::normalize(r));
		vec3 lln = math::cross(math::normalize(l), math::normalize(d));

		math::normalize(uln);
		math::normalize(urn);
		math::normalize(lrn);
		math::normalize(lln);

		normals[0 * (128) + x] = (uln + urn + lrn + lln)/4;
	}

	//lower
	for (i32 x = 0; x < 128; ++x)
	{
		vec3 u, l, r, d;

		if (x == 0)
		{
			u = normals[(128-1) * 128 + x];
			l = left[127];
			r = normals[(128-1) * 128 + (x+1)];
			d = down[x];
		}
		else if (x == 127)
		{
			u = normals[(128-1) * 128 + x];
			l = normals[(128-1) * 128 + (x-1)];
			r = right[x];
			d = down[x];
		}
		else
		{
			u = normals[(128-1-1) * 128 + x];
			l = normals[(128-1) * 128 + (x-1)];
			r = right[x];
			d = down[x];
		}

		vec3 uln = math::cross(math::normalize(u), math::normalize(l));
		vec3 urn = math::cross(math::normalize(r), math::normalize(u));
		vec3 lrn = math::cross(math::normalize(d), math::normalize(r));
		vec3 lln = math::cross(math::normalize(l), math::normalize(d));

		math::normalize(uln);
		math::normalize(urn);
		math::normalize(lrn);
		math::normalize(lln);

		normals[127 * (128) + x] = (uln + urn + lrn + lln)/4;
	}

	//left
	for (i32 y = 0; y < 128; ++y)
	{
		vec3 u, l, r, d;

		if (y == 0)
		{
			u = up[0];
			l = left[y];
			r = normals[(128-1) * 128 + (0+1)];
			d = normals[(128-1) * 128 + 0];
		}
		else if (y == (128-1))
		{
			u = normals[(y-1) * 128 + 0];
			l = left[y];
			r = normals[y * 128 + (0+1)];
			d = down[y];
		}
		else
		{
			u = normals[(y-1) * 128 + 0];
			l = left[y];
			r = normals[y * 128 + (0+1)];
			d = normals[(y+1) * 128 + (0+1)];
		}

		vec3 uln = math::cross(math::normalize(u), math::normalize(l));
		vec3 urn = math::cross(math::normalize(r), math::normalize(u));
		vec3 lrn = math::cross(math::normalize(d), math::normalize(r));
		vec3 lln = math::cross(math::normalize(l), math::normalize(d));

		math::normalize(uln);
		math::normalize(urn);
		math::normalize(lrn);
		math::normalize(lln);

		normals[y * (128) + 0] = (uln + urn + lrn + lln)/4;
	}

	//right
	for (i32 y = 0; y < 128; ++y)
	{
		vec3 u, l, r, d;

		if (y == 0)
		{
			u = up[128-1];
			l = normals[(0) * 128 + (0-1)];
			r = right[y];
			d = normals[(y+1) * 128 + 0];
		}
		else if (y == (128-1))
		{
			u = normals[(y-1) * 128 + 0];
			l = left[y];
			r = normals[y * 128 + (0+1)];
			d = down[128-1];
		}
		else
		{
			u = normals[(y-1) * 128 + 0];
			l = normals[y * 128 + (0-1)];
			r = normals[y * 128 + (0+1)];
			d = normals[(y+1) * 128 + 0];
		}

		vec3 uln = math::cross(math::normalize(u), math::normalize(l));
		vec3 urn = math::cross(math::normalize(r), math::normalize(u));
		vec3 lrn = math::cross(math::normalize(d), math::normalize(r));
		vec3 lln = math::cross(math::normalize(l), math::normalize(d));

		math::normalize(uln);
		math::normalize(urn);
		math::normalize(lrn);
		math::normalize(lln);

		normals[y * (128) + 127] = (uln + urn + lrn + lln)/4;
	}

	for (auto n : normals)
		meshn->data().push_back(n);

	tile->set_vertex_array(m_pCtx->create_vertex_array(mesh));

	m_Tiles[p] = std::move(tile);
}


void 
Terrain::draw(const std::shared_ptr<renderer::RenderContext>& ctx, const std::shared_ptr<Camera>& cam)
{
	::glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	//glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	m_pShaderProgram->use();		
	//m_pDiffuseMap->bind();
	
	auto& mvp = m_pShaderProgram->uniform<math::mat4>("r_MVP");
	auto& mv= m_pShaderProgram->uniform<math::mat4>("r_ModelView");

	for (auto iter = m_Tiles.begin(); iter != m_Tiles.end(); ++iter)
	{
		mvp = cam->projection_matrix() * cam->view_matrix() * math::Transform::translate(iter->first.x * 127, iter->first.y * 127, 0);

		// mv = cam->view_matrix() * math::Transform::translate(iter->first.first * 127, iter->first.second * 127, 0);

		auto& va = iter->second->vertex_array();
		va->bind();
		::glDrawElements(GL_TRIANGLES, va->index_count(), GL_UNSIGNED_INT, 0);

		if (m_DrawNormals)
		{
			
		}

	}
}

const std::unique_ptr<TerrainTile>&
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