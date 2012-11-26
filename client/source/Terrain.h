#ifndef TERRAIN_H_
#define TERRAIN_H_

#include "geo/Mesh.h"
#include "Image2D.h"

namespace revel
{
	
class Terrain
{
public:
	static Image2D<pixel::Gray_f32> generate_heightmap(u32 w, u32 h, f32 factor = 64.0f, f32 hscale = 10.0f)
	{
		R_LOG_ERR("IMPLEMENT MOVE OPERATOR FOR IMAGE");

		Image2D<pixel::Gray_f32> heightmap(w, h);

	    for (u32 i = 0; i < h; ++i)
	    {
	    	for (u32 j = 0; j < w; ++j)
	    	{
				heightmap(i, j) = SimplexNoise::noise(i / factor, j / factor) * hscale;
	    	}
	    }

	    return heightmap;
	}

	static std::shared_ptr<geo::Mesh> heightmap_to_mesh(const Image2D<pixel::Gray_f32>& img)
	{
		R_LOG_ERR("IMPLEMENT MOVE OPERATOR FOR MESH");

		auto mesh = std::make_shared<geo::Mesh>();    
	    auto meshp = mesh->create_vertex_attrib<point3>("position");
	    auto meshi = mesh->indices<u32>();

	    for (u32 i = 0; i < img.height(); ++i)
	    {
	    	for (u32 j = 0; j < img.width(); ++j)
	    	{
	    		meshp->data().push_back(point3(j, i, img(j, i).val));
	    	}	    	
	    }
	    

	    for (u32 i = 0; i < img.height() - 1; ++i)
	    {
	    	for (u32 j = 0; j < img.width() - 1; ++j)
	    	{
	    		meshi->add_triangle(i*128+j+128, i*128+j+128+1, i*128+j+1);
	    		meshi->add_triangle(i*128+j+1, i*128+j, i*128+j+128);
	    	}
	    }

	    return mesh;
	}	
};

}

#endif // TERRAIN_H_