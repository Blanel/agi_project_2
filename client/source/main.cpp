#include "Log.h"
#include "RenderClient.h"
#include "Config.h"


#include "TerrainManager.h"

using namespace std;

using namespace revel;

int main(int argc, char *argv[])
{
	R_LOG_INFO("Initializing");

	if (argc == 3)
	{
		std::string ip(argv[1]);
		u32 port = atoi(argv[2]);
		R_LOG_INFO("IP: " << ip);
		R_LOG_INFO("Port: " << port);

		Config::set("ip", ip);
		Config::set("port", port);
	}

	//SimplexNoise::debug();
	//TerrainManager test(20, 5, 5,5);
	//test.generate();

	RenderClient renderclient;
	return renderclient.run();
}