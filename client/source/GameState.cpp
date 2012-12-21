#include "GameState.h"
#include <limits>

namespace revel
{
	GameState::GameState()
	{
	}

	GameState::~GameState()
	{

	}
	std::pair<f32,f32> GameState::getCentre()
	{
		f32 x = 0;
		f32 y = 0;

		f32 c = 0;

		for (auto it = airplanes.begin(); it != airplanes.end(); ++it)
		{
			x += it->second.m_x;
			y += it->second.m_y;
			c++;
		}

		if (c < 1.0f)
			c = 1.0f;
		return std::make_pair(x/c, y/c);
	}

	std::pair<std::pair<f32,f32>,std::pair<f32,f32>> GameState::getBoundingBox()
	{
		if(airplanes.size()==0)
			return std::make_pair<std::pair<f32,f32>, std::pair<f32,f32>>(std::make_pair<f32,f32>(-1,-1), std::make_pair<f32,f32>(1,1));
		else
		{
			f32 xmin = std::numeric_limits<float>::max();
			f32 xmax = std::numeric_limits<float>::min();
			f32 ymin = std::numeric_limits<float>::max();
			f32 ymax = std::numeric_limits<float>::min();
			for(int i=0 ; i<airplanes.size() ;i++)
			{
				f32 tX = airplanes.at(i).m_x;
				f32 tY = airplanes.at(i).m_y;
				if(tX>xmax)
					xmax = tX;
				if(tX<xmin)
					xmin = tX;
				if(tY>ymax)
					ymax = tY;
				if(tY<ymin)
					ymin = tY;
			}
			return std::make_pair<std::pair<f32,f32>,std::pair<f32,f32>>(std::make_pair(xmin,ymin), std::make_pair(xmax,ymax));
		}
	}

	AirPlane::AirPlane()
	{
	}

	AirPlane::~AirPlane()
	{
	}

	Bullet::Bullet()
	{
	}

	Bullet::~Bullet()
	{
	}
}