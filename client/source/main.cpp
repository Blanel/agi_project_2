#include <iostream>
#include <vector>

#include "Log.h"

#include "RenderClient.h"

using namespace std;
using namespace revel;
using namespace revel::renderer;


int main(int argc, char *argv[])
{
	R_LOG_INFO("Initializing");

	RenderClient renderclient;
	return renderclient.run();
}