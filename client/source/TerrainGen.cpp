#include "TerrainGen.h"
#include "geo/Mesh.h"
#include "Noise2.h"

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


Terrain::Terrain(const std::shared_ptr<renderer::RenderContext>& ctx, i32 tile_w, i32 tile_h)
{
	m_pCtx = ctx;
	m_TileSize = vec2_i32(tile_w, tile_h);

	m_pNoiseGen = std::unique_ptr<SimplexNoise>(new SimplexNoise(0x4711));
	m_pNoiseGen->set_frequency(0.95f/128.0f);
	m_pNoiseGen->set_octaves(6);
	m_pNoiseGen->set_amplitude(2.25f);
	m_pNoiseGen->set_persistance(0.33f);

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
	u32 w = m_TileSize.x;
	u32 h = m_TileSize.y;

	std::unique_ptr<TerrainTile> tile(new TerrainTile());

	auto mesh = std::make_shared<geo::Mesh>();    
    auto meshp = mesh->create_vertex_attrib<point3>("position");
    auto meshn = mesh->create_vertex_attrib<vec3>("normals");
    auto mesht = mesh->create_vertex_attrib<vec2>("uv0");
    auto meshi = mesh->indices<u32>();

    Image2D<pixel::Gray_f32> hmap(w, h);

    i32 offset_x = p.x * m_TileSize.x;
    i32 offset_y = p.y * m_TileSize.y;

    Noise2 noise2;

	for(i32 y=0; y<h ; y++)
	{
		for(i32 x=0 ; x<w ; x++)
		{
			f32 n = 1 - fabs(m_pNoiseGen->noise(offset_x + x, offset_y + y, 0.6))*8;
			//f32 n = (1 - noise2.noise(offset_x + x, offset_y + y));
			hmap(x, y).val = n;

			meshp->data().push_back(point3(x,y,n));
			mesht->data().push_back(vec2(x / (128.0f / 16), y / (128.0f / 16)));
		}
	}

	//Triangulate mesh
	for(i32 y = 0; y < h-1 ; y++)
	{
		for(i32 x = 0; x < w-1 ; x++)
		{
			meshi->add_triangle((y+1)*w+x, (y+1)*w+(x+1), y*w+(x+1));
    		meshi->add_triangle(y*w+(x+1), y*w+x, (y+1)*w+x);
		}		
	}

	std::vector<vec3> normals(w * h, vec3::UnitZ);

	//TODO: storing half of the normals would suffice
	for (i32 y = 1; y < h-1; ++y)
	{
		for (i32 x = 1; x < w-1; ++x)
		{
			//upper left
			vec3 u = point3(x, y-1, hmap(x, y-1).val) - point3(x, y, hmap(x, y).val);
			vec3 l = point3(x-1, y, hmap(x-1, y).val) - point3(x, y, hmap(x, y).val);
			vec3 r = point3(x+1, y, hmap(x+1, y).val) - point3(x, y, hmap(x, y).val);
			vec3 d = point3(x, y+1, hmap(x, y+1).val) - point3(x, y, hmap(x, y).val);

			math::normalize(u);
			math::normalize(d);
			math::normalize(l);
			math::normalize(r);

			vec3 uln = math::cross(u, l);
			vec3 urn = math::cross(r, u);
			vec3 lrn = math::cross(d, r);
			vec3 lln = math::cross(l, d);

			normals[y * h + x] = -(uln + urn + lrn + lln)/4;
		}
	}

	//fix edge cases
	std::vector<point3> up(w);
	std::vector<point3> down(w);
	std::vector<point3> left(h);
	std::vector<point3> right(h);

	//points for adjacent tiles
	for (i32 x = 0; x < w; ++x)
	{
		up.push_back(point3(p.x * w + x, p.y * h - 1, m_pNoiseGen->noise(p.x * w + x, p.y * h - 1)));
		down.push_back(point3(p.x * w + x, p.y * h + 1, m_pNoiseGen->noise(p.x * w + x, p.y * h + 1)));
	}
	for (i32 y = 0; y < h; ++y)
	{
		left.push_back(point3(p.x * w - 1, p.y * h + y, m_pNoiseGen->noise(p.x * w - 1, p.y * h + y)));
		right.push_back(point3(p.x * w + 1, p.y * h + y, m_pNoiseGen->noise(p.x * w + 1, p.y * h + y)));
	}
	
	//upper
	for (i32 x = 0; x < w; ++x)
	{
		vec3 u, l, r, d;
		point3 p = meshp->data()[0 * w + x];

		if (x == 0)
		{
			u = up[x] - p;
			l = left[0] - p;
			r = meshp->data()[0 * w + (x+1)] - p;
			d = meshp->data()[h-1 * w + (x)] - p;
		}
		else if (x == w-1)
		{
			u = up[x] - p;
			l = meshp->data()[0 * w + (x-1)] - p;
			r = right[0] -p;
			d = meshp->data()[h-1 * w + (x)] - p;
		}
		else
		{
			u = up[x] - p;
			l = meshp->data()[0 * w + (x-1)] - p;
			r = meshp->data()[0 * w + (x+1)] - p;
			d = meshp->data()[1 * w + (x)] - p;
		}

		math::normalize(u);
		math::normalize(d);
		math::normalize(l);
		math::normalize(r);

		vec3 uln = math::cross(u, l);
		vec3 urn = math::cross(r, u);
		vec3 lrn = math::cross(d, r);
		vec3 lln = math::cross(l, d);

		normals[0 * w + x] = (uln + urn + lrn + lln)/4;
	}	

	//lower
	for (i32 x = 0; x < w; ++x)
	{
		vec3 u, l, r, d;
		point3 p = meshp->data()[(h-1) * w + x];

		if (x == 0)
		{
			u = meshp->data()[(h-2) * w + x] - p;
			l = left[h-1] - p;
			r = meshp->data()[(h-1) * w + (x+1)] - p;
			d = down[0] - p;
		}
		else if (x == w-1)
		{
			u = meshp->data()[(h-2) * w + x] - p;
			l = meshp->data()[(h-1) * w + (x-1)] - p;
			r = right[h-1] - p;
			d = down[w-1] - p;
		}
		else
		{
			u = meshp->data()[(h-2) * w + x] - p;
			l = meshp->data()[(h-1) * w + (x-1)] - p;
			r = meshp->data()[(h-1) * w + (x+1)] - p;
			d = down[x] - meshp->data()[(h-1) * w + x];
		}

		math::normalize(u);
		math::normalize(d);
		math::normalize(l);
		math::normalize(r);

		vec3 uln = math::cross(u, l);
		vec3 urn = math::cross(r, u);
		vec3 lrn = math::cross(d, r);
		vec3 lln = math::cross(l, d);

		normals[h-1 * w + x] = (uln + urn + lrn + lln)/4;
		// normals[h-1 * w + x] = vec3::UnitZ;
	}

	//left
	for (i32 y = 0; y < h; ++y)
	{
		vec3 u, l, r, d;
		point3 p = meshp->data()[y * h + 0];

		if (y == 0)
		{			
			u = up[0] - p;
			l = left[0] - p;
			r = meshp->data()[y * w + 1] - p;
			d = meshp->data()[(y+1) * w + 0] - p;
		}
		else if (y == (h-1))
		{
			u = meshp->data()[(y-1) * w + 0] - p;
			l = left[y] - p;
			r = meshp->data()[y * w + 1] - p;
			d = down[0] - p;
		}
		else
		{
			u = meshp->data()[(y-1) * w + 0] - p;
			l = left[y] - p;
			r = meshp->data()[y * w + 1] - p;
			d = meshp->data()[(y+1) * w + 0] - p;
		}

		math::normalize(u);
		math::normalize(d);
		math::normalize(l);
		math::normalize(r);

		vec3 uln = math::cross(u, l);
		vec3 urn = math::cross(r, u);
		vec3 lrn = math::cross(d, r);
		vec3 lln = math::cross(l, d);

		normals[y * w + 0] = (uln + urn + lrn + lln)/4;
		//normals[y * w + 0] = vec3::UnitZ;
	}

	//right
	for (i32 y = 0; y < h; ++y)
	{
		vec3 u, l, r, d;
		point3 p = meshp->data()[y * h + (w-1)];

		if (y == 0)
		{
			u = up[w-1] - p;
			l = meshp->data()[0 * w + (w-2)] - p;
			r = right[y] - p;
			d = meshp->data()[(y+1) * w + (w-1)] - p;
		}
		else if (y == (h-1))
		{
			u = meshp->data()[(y-1) * w + (w-1)] - p;
			l = meshp->data()[0 * w + (w-2)] - p;
			r = right[y] - p;
			d = down[w-1] - p;
		}
		else
		{
			u = meshp->data()[(y-1) * w + (w-1)] - p;
			l = meshp->data()[0 * w + (w-2)] - p;
			r = right[y] - p;
			d = meshp->data()[(y+1) * w + (w-1)] - p;
		}

		math::normalize(u);
		math::normalize(d);
		math::normalize(l);
		math::normalize(r);

		vec3 uln = math::cross(u, l);
		vec3 urn = math::cross(r, u);
		vec3 lrn = math::cross(d, r);
		vec3 lln = math::cross(l, d);

		normals[y * w + (w-1)] = (uln + urn + lrn + lln)/4;
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