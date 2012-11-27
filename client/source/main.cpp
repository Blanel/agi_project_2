#include "Log.h"
#include "RenderClient.h"


#include "TerrainManager.h"

using namespace std;

using namespace revel;

int main(int argc, char *argv[])
{
	R_LOG_INFO("Initializing");


	//SimplexNoise::debug();
	//TerrainManager test(20, 5, 5,5);
	//test.generate();

	RenderClient renderclient;
	return renderclient.run();
}