#include "Config.h"

namespace revel
{

//Load the map with default values
std::map<std::string, std::string> Config::s_ConfigMap =
{
	{"graphics_api", 	"OpenGL"},
	{"screen_width", 	"1280"},
	{"screen_height", 	"720"}
};

} /* namespace revel */
