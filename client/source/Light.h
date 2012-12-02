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

class DirectionalLight
{
	vec3 m_Direction;

public:
	DirectionalLight(const vec3& d)
		: m_Direction(d)
	{

	}

	const vec3& direction() const
	{
		return m_Direction;
	}
};
	
}