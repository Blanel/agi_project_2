#include "FrameParser.h"

namespace revel
{
	
void
FrameParser::parse_frame(const std::string& xmlframe, GameState& gs)
{
	pugi::xml_parse_result result = doc.load(xmlframe.c_str());

	auto planes = doc.child("tick").child("planes");

	for (auto p = planes.child("p"); p; p = p.next_sibling("p"))
	{
		auto id = p.attribute("id").as_int();
		f32 x = p.child("x").text().as_double();
		f32 y = p.child("y").text().as_double();
		f32 a = p.child("a").text().as_double();
		i32 status = p.child("status").text().as_int();

		if (status == 1)
		{
			gs.create_plane(id,x,y,a);
		}
		else
		{
			gs.update_plane(id,x,y,a);
		}
	}
}

}