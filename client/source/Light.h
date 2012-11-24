#include "math/Vector3.h"
#include "math/Point3.h"

namespace revel
{

enum class LightType
{
	SPOT,
	POINT,
	DIRECTIONAL
};

class Light
{
	point3 	m_Position;
	vec3 	m_Direction;
	
public:
	Light(LightType type)
	{}
	
};
	
}