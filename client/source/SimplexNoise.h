#include "Types.h"
#include <array>
#include <vector>
#include <cmath>
#include "math/RMath.h"

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

	static f32 dot(const Grad& g, f32 x, f32 y)
	{
		return g.x * x + g.y * y;
	}

	static f32 dot(const Grad& g, f32 x, f32 y, f32 z)
	{
		return g.x * x + g.y * y + g.z * z;
	}

	static f32 dot(const Grad& g, f32 x, f32 y, f32 z, f32 w)
	{
		return g.x * x + g.y * y + g.z * z + g.w * w;
	}


	static std::array<u8, 512> p;
	static std::array<u8, 512> pmod12;

	static std::array<Grad, 12> grad3;
	static std::array<Grad, 32> grad4;

	static f32 F2, G2, F3, G3, F4, G4;


	static std::array<u8, 512> init_array()
	{
		std::array<u8, 512> array = p;

		for (auto& i : array)
		{
			i = i%12;
		}

		return array;
	}

public:
	static f32 noise(f32 x, f32 y);

	static f32 noise(f32 x, f32 y, f32 z);

	static f32 noise(f32 x, f32 y, f32 z, f32 w);


	static void debug()
	{
		R_LOG_INFO("DEBUG: " << (i32)pmod12[0]);
		R_LOG_INFO("DEBUG: " << grad3[0].y);
	}


};
	
} // ::revel