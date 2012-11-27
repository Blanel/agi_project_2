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
	Light();
	virtual ~Light();

	const point3& position() const;
	void set_position(f32 x, f32 y, f32 z);
	void set_position(const point3& p);
	
};
	
}