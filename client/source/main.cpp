#include "Log.h"
#include "RenderClient.h"

using namespace revel;

int main(int argc, char *argv[])
{
	R_LOG_INFO("Initializing");
	RenderClient renderclient;
	return renderclient.run();
}