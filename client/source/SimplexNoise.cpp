#include "SimplexNoise.h"
#include <cmath>
#include <algorithm>

namespace revel
{

f32 SimplexNoise::F2 = 0.5*(sqrt(3.0)-1.0);
f32 SimplexNoise::G2 = (3.0 - sqrt(3.0))/6.0;
f32 SimplexNoise::F3 = (1.0 / 3.0);
f32 SimplexNoise::G3 = (1.0 / 6.0);
f32 SimplexNoise::F4 = (sqrt(5.0) - 1.0)/4.0;
f32 SimplexNoise::G4 = (5.0 - sqrt(5.0))/20.0;

std::array<SimplexNoise::Grad, 12>
SimplexNoise::grad3 = 
{
	SimplexNoise::Grad(1,1,0), 		SimplexNoise::Grad(-1,1,0), 	SimplexNoise::Grad(1,-1,0), 	SimplexNoise::Grad(-1,-1,0),
 	SimplexNoise::Grad(1,0,1), 		SimplexNoise::Grad(-1,0,1), 	SimplexNoise::Grad(1,0,-1), 	SimplexNoise::Grad(-1,0,-1),
 	SimplexNoise::Grad(0,1,1), 		SimplexNoise::Grad(0,-1,1), 	SimplexNoise::Grad(0,1,-1), 	SimplexNoise::Grad(0,-1,-1)
};

std::array<SimplexNoise::Grad, 32>
SimplexNoise::grad4 = 
{
	SimplexNoise::Grad(0,1,1,1),	SimplexNoise::Grad(0,1,1,-1),	SimplexNoise::Grad(0,1,-1,1),	SimplexNoise::Grad(0,1,-1,-1),
	SimplexNoise::Grad(0,-1,1,1),	SimplexNoise::Grad(0,-1,1,-1),	SimplexNoise::Grad(0,-1,-1,1),	SimplexNoise::Grad(0,-1,-1,-1),
	SimplexNoise::Grad(1,0,1,1),	SimplexNoise::Grad(1,0,1,-1),	SimplexNoise::Grad(1,0,-1,1),	SimplexNoise::Grad(1,0,-1,-1),
	SimplexNoise::Grad(-1,0,1,1),	SimplexNoise::Grad(-1,0,1,-1),	SimplexNoise::Grad(-1,0,-1,1),	SimplexNoise::Grad(-1,0,-1,-1),
	SimplexNoise::Grad(1,1,0,1),	SimplexNoise::Grad(1,1,0,-1),	SimplexNoise::Grad(1,-1,0,1),	SimplexNoise::Grad(1,-1,0,-1),
	SimplexNoise::Grad(-1,1,0,1),	SimplexNoise::Grad(-1,1,0,-1),	SimplexNoise::Grad(-1,-1,0,1),	SimplexNoise::Grad(-1,-1,0,-1),
	SimplexNoise::Grad(1,1,1,0),	SimplexNoise::Grad(1,1,-1,0),	SimplexNoise::Grad(1,-1,1,0),	SimplexNoise::Grad(1,-1,-1,0),
	SimplexNoise::Grad(-1,1,1,0),	SimplexNoise::Grad(-1,1,-1,0),	SimplexNoise::Grad(-1,-1,1,0),	SimplexNoise::Grad(-1,-1,-1,0)
};

SimplexNoise::SimplexNoise()
{

    p = std::vector<u8>{151,160,137,91,90,15,
      131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
      190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
      88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
      77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
      102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
      135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
      5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
      223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
      129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
      251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
      49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
      138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180};

    p.insert(p.end(), p.begin(), p.end());

    pmod12 = p; 
    for (auto& i : pmod12)
    {
        i = i%12;
    }

    m_Amplitude = 1.0f;

}

SimplexNoise::SimplexNoise(u32 seed)
{
    p.resize(256);
    std::iota(p.begin(), p.end(), 0);

    std::mt19937 rng(seed);
    std::shuffle(p.begin(), p.end(), rng);

    p.insert(p.end(), p.begin(), p.end());
    pmod12 = p;

    for (auto& i : pmod12)
    {
        i = i%12;
    }

    m_Amplitude = 1.0f;
}

f32
SimplexNoise::noise(f32 x, f32 y)
{
    f32 t = 0.0f;
    f32 a = 1.0f;
    f32 f = m_Frequency;

    for (u32 k = 0; k < m_Octaves; ++k)
    {
        t += noise_value(x * f, y * f) * a;
        a *= m_Persitence;
        f *= 2;
    }

    return t * m_Amplitude;
}

f32
SimplexNoise::noise(f32 x, f32 y, f32 z)
{
    f32 t = 0.0f;
    f32 a = 1.0f;
    f32 f = m_Frequency;

    for (u32 k = 0; k < m_Octaves; ++k)
    {
        t += noise_value(x * f, y * f, z * f) * a;
        a *= m_Persitence;
        f *= 2;
    }

    return t * m_Amplitude;
}

f32
SimplexNoise::noise(f32 x, f32 y, f32 z, f32 w)
{
    f32 t = 0.0f;
    f32 a = 1.0f;
    f32 f = m_Frequency;

    for (u32 k = 0; k < m_Octaves; ++k)
    {
        t += noise_value(z * f, y * f, z * f, w * f) * a;
        a *= m_Persitence;
        f *= 2;
    }

    return t * m_Amplitude;
}

f32 
SimplexNoise::noise_value(f32 xin, f32 yin)
{
	// Noise contributions from the three corners
	f32 n0, n1, n2; 

	// Skew the input space to determine which simplex cell we're in
	f32 s = (xin+yin)*F2; // Hairy factor for 2D

	i32 i = math::ffloor(xin+s);
	i32 j = math::ffloor(yin+s);
		f32 t = (i+j)*G2;
	f32 X0 = i-t; // Unskew the cell origin back to (x,y) space
	f32 Y0 = j-t;
	f32 x0 = xin-X0; // The x,y distances from the cell origin
	f32 y0 = yin-Y0;

	// For the 2D case, the simplex shape is an equilateral triangle.
	// Determine which simplex we are in.
	int i1, j1; // Offsets for second (middle) corner of simplex in (i,j) coords

	if(x0>y0) // lower triangle, XY order: (0,0)->(1,0)->(1,1)
	{
		i1=1; 
		j1=0;
	} 
	else       // upper triangle, YX order: (0,0)->(0,1)->(1,1)
	{
		i1=0; 
		j1=1;
	}

	// A step of (1,0) in (i,j) means a step of (1-c,-c) in (x,y), and
	// a step of (0,1) in (i,j) means a step of (-c,1-c) in (x,y), where
	// c = (3-sqrt(3))/6
	f32 x1 = x0 - i1 + G2; // Offsets for middle corner in (x,y) unskewed coords
	f32 y1 = y0 - j1 + G2;
	f32 x2 = x0 - 1.0 + 2.0 * G2; // Offsets for last corner in (x,y) unskewed coords
	f32 y2 = y0 - 1.0 + 2.0 * G2;

	// Work out the hashed gradient indices of the three simplex corners
	i32 ii = i & 255;
	i32 jj = j & 255;
	i32 gi0 = pmod12[ii+p[jj]];
	i32 gi1 = pmod12[ii+i1+p[jj+j1]];
	i32 gi2 = pmod12[ii+1+p[jj+1]];

	// Calculate the contribution from the three corners
	f32 t0 = 0.5 - x0*x0-y0*y0;
	if(t0<0) 
	{
		n0 = 0.0;
	}
	else 
	{
	  	t0 *= t0;
	  	n0 = t0 * t0 * dot(grad3[gi0], x0, y0);  // (x,y) of grad3 used for 2D gradient
	}

	f32 t1 = 0.5 - x1*x1-y1*y1;	    
	if(t1<0)
	{
		n1 = 0.0;
	}
	else 
	{
	  	t1 *= t1;
	  	n1 = t1 * t1 * dot(grad3[gi1], x1, y1);
	}

	f32 t2 = 0.5 - x2*x2-y2*y2;
	if(t2<0)
	{ 
		n2 = 0.0;
	}
	else 
	{
	  	t2 *= t2;
	  	n2 = t2 * t2 * dot(grad3[gi2], x2, y2);
	}

	// Add contributions from each corner to get the final noise value.
	// The result is scaled to return values in the interval [-1,1].
	return 70.0 * (n0 + n1 + n2) * m_Amplitude;
}


// 3D simplex noise
f32 SimplexNoise::noise_value(f32 xin, f32 yin, f32 zin) 
{
    f32 n0, n1, n2, n3; // Noise contributions from the four corners
    
    // Skew the input space to determine which simplex cell we're in
    f32 s = (xin+yin+zin)*F3; // Very nice and simple skew factor for 3D
    i32 i = math::ffloor(xin+s);
    i32 j = math::ffloor(yin+s);
    i32 k = math::ffloor(zin+s);    
    f32 t = (i+j+k)*G3;
    f32 X0 = i-t; // Unskew the cell origin back to (x,y,z) space
    f32 Y0 = j-t;
    f32 Z0 = k-t;
    f32 x0 = xin-X0; // The x,y,z distances from the cell origin
    f32 y0 = yin-Y0;
    f32 z0 = zin-Z0;

    // For the 3D case, the simplex shape is a slightly irregular tetrahedron.
    // Determine which simplex we are in.
    i32 i1, j1, k1; // Offsets for second corner of simplex in (i,j,k) coords
    i32 i2, j2, k2; // Offsets for third corner of simplex in (i,j,k) coords
    if(x0>=y0) 
    {
      	if(y0>=z0) // X Y Z order
    	{ 
    		i1=1; j1=0; k1=0; i2=1; j2=1; k2=0; 
		} 
    	else if(x0>=z0) // X Z Y order
    	{ 
    		i1=1; j1=0; k1=0; i2=1; j2=0; k2=1; 
    	} 
        else // Z X Y order
        { 
        	i1=0; j1=0; k1=1; i2=1; j2=0; k2=1; 
    	} 
  	}
    else // x0<y0
    { 
      	if(y0<z0) // Z Y X order
      	{ 
      		i1=0; j1=0; k1=1; i2=0; j2=1; k2=1; 
      	} 
      	else if(x0<z0) // Y Z X order
      	{ 
      		i1=0; j1=1; k1=0; i2=0; j2=1; k2=1; 
      	} 
      	else // Y X Z order
      	{ 
      		i1=0; j1=1; k1=0; i2=1; j2=1; k2=0; 
  		} 
    }

    // A step of (1,0,0) in (i,j,k) means a step of (1-c,-c,-c) in (x,y,z),
    // a step of (0,1,0) in (i,j,k) means a step of (-c,1-c,-c) in (x,y,z), and
    // a step of (0,0,1) in (i,j,k) means a step of (-c,-c,1-c) in (x,y,z), where
    // c = 1/6.
    f32 x1 = x0 - i1 + G3; // Offsets for second corner in (x,y,z) coords
    f32 y1 = y0 - j1 + G3;
    f32 z1 = z0 - k1 + G3;
    f32 x2 = x0 - i2 + 2.0*G3; // Offsets for third corner in (x,y,z) coords
    f32 y2 = y0 - j2 + 2.0*G3;
    f32 z2 = z0 - k2 + 2.0*G3;
    f32 x3 = x0 - 1.0 + 3.0*G3; // Offsets for last corner in (x,y,z) coords
    f32 y3 = y0 - 1.0 + 3.0*G3;
    f32 z3 = z0 - 1.0 + 3.0*G3;

    // Work out the hashed gradient indices of the four simplex corners
    i32 ii = i & 255;
    i32 jj = j & 255;
    i32 kk = k & 255;
    i32 gi0 = pmod12[ii+p[jj+p[kk]]];
    i32 gi1 = pmod12[ii+i1+p[jj+j1+p[kk+k1]]];
    i32 gi2 = pmod12[ii+i2+p[jj+j2+p[kk+k2]]];
    i32 gi3 = pmod12[ii+1+p[jj+1+p[kk+1]]];

    // Calculate the contribution from the four corners
    f32 t0 = 0.6 - x0*x0 - y0*y0 - z0*z0;
    if(t0<0) 
    {
    	n0 = 0.0;
    }
    else 
    {
      	t0 *= t0;
      	n0 = t0 * t0 * dot(grad3[gi0], x0, y0, z0);
    }

    f32 t1 = 0.6 - x1*x1 - y1*y1 - z1*z1;

    if(t1<0) 
	{
		n1 = 0.0;
	}
    else 
    {
      	t1 *= t1;
      	n1 = t1 * t1 * dot(grad3[gi1], x1, y1, z1);
    }

    f32 t2 = 0.6 - x2*x2 - y2*y2 - z2*z2;

    if(t2<0) 
	{
		n2 = 0.0;
	}
    else 
    {
      	t2 *= t2;
      	n2 = t2 * t2 * dot(grad3[gi2], x2, y2, z2);
    }

    f32 t3 = 0.6 - x3*x3 - y3*y3 - z3*z3;
    
    if(t3<0) 
	{	
		n3 = 0.0;
	}
    else 
    {
		t3 *= t3;
		n3 = t3 * t3 * dot(grad3[gi3], x3, y3, z3);
    }
    
    // Add contributions from each corner to get the final noise value.
    // The result is scaled to stay just inside [-1,1]
    return 32.0*(n0 + n1 + n2 + n3) * m_Amplitude;
  }


  // 4D simplex noise, better simplex rank ordering method 2012-03-09
f32 
SimplexNoise::noise_value(f32 x, f32 y, f32 z, f32 w) 
{
    f32 n0, n1, n2, n3, n4; // Noise contributions from the five corners
    
    // Skew the (x,y,z,w) space to determine which cell of 24 simplices we're in
    f32 s = (x + y + z + w) * F4; // Factor for 4D skewing
    i32 i = math::ffloor(x + s);
    i32 j = math::ffloor(y + s);
    i32 k = math::ffloor(z + s);
    i32 l = math::ffloor(w + s);
    f32 t = (i + j + k + l) * G4; // Factor for 4D unskewing
    f32 X0 = i - t; // Unskew the cell origin back to (x,y,z,w) space
    f32 Y0 = j - t;
    f32 Z0 = k - t;
    f32 W0 = l - t;
    f32 x0 = x - X0;  // The x,y,z,w distances from the cell origin
    f32 y0 = y - Y0;
    f32 z0 = z - Z0;
    f32 w0 = w - W0;

    // For the 4D case, the simplex is a 4D shape I won't even try to describe.
    // To find out which of the 24 possible simplices we're in, we need to
    // determine the magnitude ordering of x0, y0, z0 and w0.
    // Six pair-wise comparisons are performed between each possible pair
    // of the four coordinates, and the results are used to rank the numbers.
    i32 rankx = 0;
    i32 ranky = 0;
    i32 rankz = 0;
    i32 rankw = 0;

    if(x0 > y0) rankx++; else ranky++;
    if(x0 > z0) rankx++; else rankz++;
    if(x0 > w0) rankx++; else rankw++;
    if(y0 > z0) ranky++; else rankz++;
    if(y0 > w0) ranky++; else rankw++;
    if(z0 > w0) rankz++; else rankw++;

    i32 i1, j1, k1, l1; // The integer offsets for the second simplex corner
    i32 i2, j2, k2, l2; // The integer offsets for the third simplex corner
    i32 i3, j3, k3, l3; // The integer offsets for the fourth simplex corner
   
    // simplex[c] is a 4-vector with the numbers 0, 1, 2 and 3 in some order.
    // Many values of c will never occur, since e.g. x>y>z>w makes x<z, y<w and x<w
    // impossible. Only the 24 indices which have non-zero entries make any sense.
    // We use a thresholding to set the coordinates in turn from the largest magnitude.
    
    // Rank 3 denotes the largest coordinate.
    i1 = rankx >= 3 ? 1 : 0;
    j1 = ranky >= 3 ? 1 : 0;
    k1 = rankz >= 3 ? 1 : 0;
    l1 = rankw >= 3 ? 1 : 0;
    
    // Rank 2 denotes the second largest coordinate.
    i2 = rankx >= 2 ? 1 : 0;
    j2 = ranky >= 2 ? 1 : 0;
    k2 = rankz >= 2 ? 1 : 0;
    l2 = rankw >= 2 ? 1 : 0;
    
    // Rank 1 denotes the second smallest coordinate.
    i3 = rankx >= 1 ? 1 : 0;
    j3 = ranky >= 1 ? 1 : 0;
    k3 = rankz >= 1 ? 1 : 0;
    l3 = rankw >= 1 ? 1 : 0;
    
    // The fifth corner has all coordinate offsets = 1, so no need to compute that.
    f32 x1 = x0 - i1 + G4; // Offsets for second corner in (x,y,z,w) coords
    f32 y1 = y0 - j1 + G4;
    f32 z1 = z0 - k1 + G4;
    f32 w1 = w0 - l1 + G4;
    f32 x2 = x0 - i2 + 2.0*G4; // Offsets for third corner in (x,y,z,w) coords
    f32 y2 = y0 - j2 + 2.0*G4;
    f32 z2 = z0 - k2 + 2.0*G4;
    f32 w2 = w0 - l2 + 2.0*G4;
    f32 x3 = x0 - i3 + 3.0*G4; // Offsets for fourth corner in (x,y,z,w) coords
    f32 y3 = y0 - j3 + 3.0*G4;
    f32 z3 = z0 - k3 + 3.0*G4;
    f32 w3 = w0 - l3 + 3.0*G4;
    f32 x4 = x0 - 1.0 + 4.0*G4; // Offsets for last corner in (x,y,z,w) coords
    f32 y4 = y0 - 1.0 + 4.0*G4;
    f32 z4 = z0 - 1.0 + 4.0*G4;
    f32 w4 = w0 - 1.0 + 4.0*G4;
    
    // Work out the hashed gradient indices of the five simplex corners
    i32 ii = i & 255;
    i32 jj = j & 255;
    i32 kk = k & 255;
    i32 ll = l & 255;
    i32 gi0 = p[ii+p[jj+p[kk+p[ll]]]] % 32;
    i32 gi1 = p[ii+i1+p[jj+j1+p[kk+k1+p[ll+l1]]]] % 32;
    i32 gi2 = p[ii+i2+p[jj+j2+p[kk+k2+p[ll+l2]]]] % 32;
    i32 gi3 = p[ii+i3+p[jj+j3+p[kk+k3+p[ll+l3]]]] % 32;
    i32 gi4 = p[ii+1+p[jj+1+p[kk+1+p[ll+1]]]] % 32;
    
    // Calculate the contribution from the five corners
    f32 t0 = 0.6 - x0*x0 - y0*y0 - z0*z0 - w0*w0;
    if(t0<0) 
    {
        n0 = 0.0;
    }
    else 
    {
        t0 *= t0;
        n0 = t0 * t0 * dot(grad4[gi0], x0, y0, z0, w0);
    }
    
    f32 t1 = 0.6 - x1*x1 - y1*y1 - z1*z1 - w1*w1;
    if(t1<0)
    {   
        n1 = 0.0;
    }
    else 
    {
        t1 *= t1;
        n1 = t1 * t1 * dot(grad4[gi1], x1, y1, z1, w1);
    }
    
    f32 t2 = 0.6 - x2*x2 - y2*y2 - z2*z2 - w2*w2;
    if(t2<0)
    { 
        n2 = 0.0;
    }
    else 
    {
        t2 *= t2;
        n2 = t2 * t2 * dot(grad4[gi2], x2, y2, z2, w2);
    }
   
    f32 t3 = 0.6 - x3*x3 - y3*y3 - z3*z3 - w3*w3;
    if(t3<0)
    {
        n3 = 0.0;
    }
    else 
    {
        t3 *= t3;
        n3 = t3 * t3 * dot(grad4[gi3], x3, y3, z3, w3);
    }
   
    f32 t4 = 0.6 - x4*x4 - y4*y4 - z4*z4 - w4*w4;
    if(t4<0)
    { 
        n4 = 0.0;
    }
    else 
    {
        t4 *= t4;
        n4 = t4 * t4 * dot(grad4[gi4], x4, y4, z4, w4);
    }
    
    // Sum up and scale the result to cover the range [-1,1]
    return 27.0 * (n0 + n1 + n2 + n3 + n4) * m_Amplitude;
}

void
SimplexNoise::set_amplitude(f32 a)
{
    m_Amplitude = a;
}

f32 
SimplexNoise::amplitude() const
{
    return m_Amplitude;
}

void
SimplexNoise::set_persistance(f32 p)
{
    m_Persitence = p;
}

f32
SimplexNoise::persistance() const
{
    return m_Persitence;
}

void
SimplexNoise::set_frequency(f32 f)
{
    m_Frequency = f;
}

f32
SimplexNoise::frequency() const
{
    return m_Frequency;
}

void
SimplexNoise::set_octaves(u32 o)
{
    m_Octaves = o;
}

u32
SimplexNoise::octaves() const
{
    return m_Octaves;
}

} // ::revel