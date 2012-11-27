#ifndef TERRAINTILE_H_
#define TERRAINTILE_H_
#include "geo/Mesh.h"
namespace revel
{

class TerrainTile
{
	
public:
	TerrainTile(float x, float y, int res, float len, float hei);
	~TerrainTile();
	std::shared_ptr<geo::Mesh> mesh;
};

}

#endif