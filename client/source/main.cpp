#include <iostream>
#include <vector>

#include "Log.h"

#include "RenderClient.h"

using namespace std;
using namespace revel;
using namespace revel::renderer;

#include "SimplexNoise.h"

int main(int argc, char *argv[])
{
	R_LOG_INFO("Initializing");

	f32 x = SimplexNoise::noise(1, 1);

	R_LOG_INFO("NOISE: " << x);

	SimplexNoise::debug();

	RenderClient renderclient;
	return renderclient.run();
}