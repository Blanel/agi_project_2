#include "TerrainTile.h"
#include "SimplexNoise.h"

namespace revel
{
	TerrainTile::TerrainTile(float x, float y, int res, float len)
	{
		//auto tilep = tile.create_vertex_attrib<vec3_f32>("position");
		f32 d = (f32)len/(f32)res;
		for(int i=0; i<=res ; i++)
		{
			for(int j=0 ; j<=res ; j++)
			{
				//std::cout<<SimplexNoise::noise(x+j*d,y+i*d)<<" ";
				//vec3_f32 vert(x+j*d, y+i*d, SimplexNoise::noise(x+j*d,y+i*d)); 

				//tilep->data().push_back(vert);
			}
			std::cout<<"\n";
		}
	}

	TerrainTile::~TerrainTile()
	{

	}
}