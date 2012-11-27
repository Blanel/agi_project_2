#include "TerrainTile.h"
#include "SimplexNoise.h"

namespace revel
{
	TerrainTile::TerrainTile(float x, float y, int res, float len, float hei)
	{
		mesh = std::make_shared<geo::Mesh>();    
	    auto meshp = mesh->create_vertex_attrib<point3>("position");
	    auto meshi = mesh->indices<u32>();
		
		f32 d = (f32)len/(f32)res;
		for(int i=0; i<res ; i++)
		{
			for(int j=0 ; j<res ; j++)
			{
				//std::cout<<SimplexNoise::noise(x+j*d,y+i*d)<<" ";
				//vec3_f32 vert(x+j*d, y+i*d, SimplexNoise::noise(x+j*d,y+i*d)); 

				//tilep->data().push_back(vert);
				meshp->data().push_back(point3(j,i,SimplexNoise::noise(x+j*d,y+i*d)*hei));
			}
			//std::cout<<"\n";
		}

		for(int i = 0 ; i < res -1 ; i++)
		{
			for(int j = 0 ; j < res -1 ; j++)
			{
				meshi->add_triangle(i*res+j+res, i*res+j+res+1, i*res+j+1);
	    		meshi->add_triangle(i*res+j+1, i*res+j, i*res+j+res);
			}
		}
	}

	TerrainTile::~TerrainTile()
	{

	}
}