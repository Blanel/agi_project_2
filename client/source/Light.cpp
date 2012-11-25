#include "Light.h"

namespace revel
{

Light::Light()
{

}	

Light::~Light()
{

}

void
Light::set_position(const point3& p)
{
	m_Position = p;
}

void
Light::set_position(f32 x, f32 y, f32 z)
{
	m_Position = point3(x, y, z);
}

const point3&
Light::position() const
{
	return m_Position;
}

	
}