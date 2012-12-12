#include "FrameParser.h"

namespace revel
{
	
void
FrameParser::parse_frame(const std::string& xmlframe, GameState& gs)
{
	pugi::xml_parse_result result = doc.load(xmlframe.c_str());

	auto planes = doc.child("tick").child("planes");
	auto bullets = doc.child("tick").child("bullets");

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
		else if(status == 0)
		{
			gs.update_plane(id,x,y,a, true);
		}
		else
		{
			gs.update_plane(id,x,y,a,false);
		}
	}
	for (auto b = bullets.child("b"); b; b = b.next_sibling("b"))
	{
		auto id = b.attribute("id").as_int();
		f32 x = b.child("x").text().as_double();
		f32 y = b.child("y").text().as_double();
		f32 a = b.child("a").text().as_double();
		i32 status = b.child("status").text().as_int();

		if (status == 1)
		{
			gs.create_bullet(id,x,y,a);
		}
		else if(status == 0)
		{
			gs.update_bullet(id,x,y,a, true, false);
		}
		else if(status == -1)
		{
			gs.update_bullet(id,x,y,a,false, true);
		}
		else
		{
			gs.update_bullet(id,x,y,a,false, false);
		}
	}
}

}