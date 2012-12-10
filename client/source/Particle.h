#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "math/Point3.h"
#include "math/Vector3.h"
#include <vector>

namespace revel
{
	
class Particle
{
	point3 	m_Location;
	vec3 	m_Direction;
	vec3 	m_Velocity;
	f32 	m_Radius;

public:

	void update(f32 dt)
	{
		m_Location += m_Direction * m_Velocity * dt;
	}

	void draw()
	{

	}


};

class ParticleController
{
	std::vector<Particle> m_Particles;

public:
	ParticleController()
	{

	}

	virtual ~ParticleController()
	{

	}

	void update(f32 dt)
	{
		for(auto& p : m_Particles)
		{
			p.update(dt);
		}
	}

};

}

#endif // PARTICLE_H_