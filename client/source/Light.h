#ifndef LIGHT_H_
#define LIGHT_H_

#include "math/Vector3.h"
#include "math/Point3.h"

namespace revel
{

class Light
{
public:
	Light();
	virtual ~Light();
	
};

class DirectionalLight : public Light
{
	vec3 m_Direction;

public:
	DirectionalLight(const vec3& d);

	const vec3& direction() const;
	void set_direction(const vec3& d);
};
	
}

#endif // LIGHT_H_