#ifndef FRAMEPARSER_H_
#define FRAMEPARSER_H_

#include "GameState.h"
#include <string>
#include "pugixml.hpp"

namespace revel
{

class FrameParser
{
    pugi::xml_document doc;    
    
public:
	void parse_frame(const std::string& xmlframe, GameState& gs);
	
};
	
}

#endif // FRAMEPARSER_H_