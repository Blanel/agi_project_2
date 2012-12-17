#ifndef PERLINNOISE_H_
#define PERLINNOISE_H_

#include "math/RMath.h"
#include "Types.h"
#include "math/Point3.h"
#include <vector>

namespace revel
{

class PerlinNoise
{
	f32 grad(i32 x, i32 y, i32 z, f32 dx, f32 dy, f32 dz)
	{
		i32 h = p[p[p[x]+y]+z];

		h &= 15;

		f32 u = h<8 || h == 12 || h == 13 ? dx : dy;
		f32 v = h<4 || h == 12 || h == 13 ? dy : dz;
		return ((h&1) ? -u : u) + ((h&2) ? -v : v);
	}

	f32 weight(f32 t)
	{
		f32 t3 = t*t*t;
		f32 t4 = t3*t;
		return 6.0f * t4 * t - 15.0f * t4 + 10.0f * t3;
	}

	std::vector<u8> p;

	f32 m_Amplitude;
	f32 m_Persistence;
	u32 m_Octaves;

public:
	PerlinNoise();
	PerlinNoise(u32 seed);
	~PerlinNoise();

	f32 noise(f32 x, f32 y, f32 z);
	f32 noise(const point3& p);
};


}

#endif // PERLINNOISE_H_
