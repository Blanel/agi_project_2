#ifndef NOISE2_H_
#define NOISE2_H_

#include "Types.h"
#include <cmath>

namespace revel
{
	

class Noise2
{
public:
	inline double findnoise2(double x,double y)
	{
		int n=(int)x+(int)y*57;
		n=(n<<13)^n;
		int nn=(n*(n*n*60493+19990303)+1376312589)&0x7fffffff;
		return 1.0-((double)nn/1073741824.0);
	}

	inline double interpolate(double a,double b,double x)
	{
	 double ft=x * 3.1415927;
	 double f=(1.0-cos(ft))* 0.5;
	 return a*(1.0-f)+b*f;
	}

	double noise_value(double x,double y)
	{
		double floorx=(double)((int)x);//This is kinda a cheap way to floor a double integer.
		double floory=(double)((int)y);
		double s,t,u,v;//Integer declaration
		s=findnoise2(floorx,floory); 
		t=findnoise2(floorx+1,floory);
		u=findnoise2(floorx,floory+1);//Get the surrounding pixels to calculate the transition.
		v=findnoise2(floorx+1,floory+1);
		double int1=interpolate(s,t,x-floorx);//Interpolate between the values.
		double int2=interpolate(u,v,x-floorx);//Here we use x-floorx, to get 1st dimension. Don't mind the x-floorx thingie, it's part of the cosine formula.
		
		return interpolate(int1,int2,y-floory);//Here we use y-floory, to get the 2nd dimension.
	}

	double noise(double x, double y)
	{
		f32 zoom = 256.0f / 4.0f;

		i32 octaves = 6;
		f32 persitance = 0.5f;

		//f32 freq = 2.0f;
		f32 amp = 0.5f;
		f64 n = 0.0;

		for (i32 a = 0; a < (octaves-1); ++a)
		{
			f32 freq = pow(2, a);
			f32 amp = pow(persitance, a);
			n += noise_value(x * freq / zoom, y * freq / zoom)*amp;
		}

		return n;
	}
};



}

#endif // NOISE2_H_