#include "TerrainTile.h"
#include "SimplexNoise.h"

namespace revel
{
	TerrainTile::TerrainTile(float x, float y, int res, float len)
	{
		f32 d = (f32)len/(f32)res;
		for(int i=0; i<=res ; i++)
		{
			for(int j=0 ; j<=res ; j++)
			{
				std::cout<<SimplexNoise::noise(x+j*d,y+i*d)<<" ";
			}
			std::cout<<"\n";
		}
	}

	TerrainTile::~TerrainTile()
	{

	}
}