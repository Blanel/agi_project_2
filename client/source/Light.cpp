#include "Light.h"

namespace revel
{

Light::Light()
{

}	

Light::~Light()
{

}


DirectionalLight::DirectionalLight(const vec3& d)
	: m_Direction(d)
{}	


const vec3& 
DirectionalLight::direction() const
{
	return m_Direction;
}

void
DirectionalLight::set_direction(const vec3& d)
{
	m_Direction = d;
}

} // ::revel