#ifndef SIMPLEXNOISE_H_
#define SIMPLEXNOISE_H_
#include "Types.h"
#include <array>
#include <vector>
#include <cmath>
#include "math/RMath.h"

#include <random>
#include <algorithm>
#include "Log.h"

// borrowed code from www.itn.liu.se/~stegu/simplexnoise/SimplexNoise.java

namespace revel
{

class SimplexNoise
{
	struct Grad
	{
		f32 x, y, z, w;

		Grad(f32 x, f32 y, f32 z)
			: x(x), y(y), z(z), w(0)
		{}

		Grad(f32 x, f32 y, f32 z, f32 w)
			: x(x), y(y), z(z), w(w)
		{}
	};

	f32 dot(const Grad& g, f32 x, f32 y)
	{
		return g.x * x + g.y * y;
	}

	f32 dot(const Grad& g, f32 x, f32 y, f32 z)
	{
		return g.x * x + g.y * y + g.z * z;
	}

	f32 dot(const Grad& g, f32 x, f32 y, f32 z, f32 w)
	{
		return g.x * x + g.y * y + g.z * z + g.w * w;
	}


	std::vector<u8> p;
	std::vector<u8> pmod12;

	static std::array<Grad, 12> grad3;
	static std::array<Grad, 32> grad4;
	static f32 F2, G2, F3, G3, F4, G4;

	f32 m_Amplitude;
	f32 m_Frequency;
	f32 m_Persitence;
	u32 m_Octaves;

	f32 noise_value(f32 x, f32 y);
	f32 noise_value(f32 x, f32 y, f32 z);
	f32 noise_value(f32 x, f32 y, f32 z, f32 w);

public:
	SimplexNoise();
	SimplexNoise(u32 seed);

	void set_amplitude(f32 a);
	f32 amplitude() const;

	void set_frequency(f32 f);
	f32 frequency() const;

	void set_persistance(f32 p);
	f32 persistance() const;

	void set_octaves(u32 o);
	u32 octaves() const;

	f32 noise_fractal_brownian_motion(i32 octaves, f32 x, f32 y, f32 z)
	{
		const f32 lacunarity = 1.9;
		const f32 gain = 0.65;

		f32 sum = 0.0f;
		f32 amplitude = 1.0f;

		for (i32 i = 0; i < octaves; ++i)
		{
			sum += noise_value(x, y, z);
			amplitude *= gain;

			x*=lacunarity;
			y*=lacunarity;
			z*=lacunarity;
		}

		return sum;
	}

	f32 turbulence(f32 x, f32 y, i32 octaves, f32 lacunarity = 2.0f, f32 gain = 0.5f)
	{
		
	}

	f32 noise(f32 x, f32 y);
	f32 noise(f32 x, f32 y, f32 z);
	f32 noise(f32 x, f32 y, f32 z, f32 w);

};
	
} // ::revel

#endif