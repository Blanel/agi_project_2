#include <map>

#include "Types.h"
#include "math/Vector2.h"
#include "TerrainTile.h"

namespace revel
{
	class TerrainManager
	{
		int optimalChunks;
		std::map<vec2_i32, TerrainTile*> tiles;
		int chunkRes;
		int chunkLen;
	public:
		TerrainManager(int optimalChunks, int chunkRes, int chunkLen);
		~TerrainManager();
		void prune();
		void generate();
	};
}