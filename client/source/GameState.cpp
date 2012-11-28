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
		if(airplanes.size()==0)
			return std::make_pair<f32,f32>(0,0);
		else
		{
			f32 x;
			f32 y;
			for(i32 i=0 ; i<airplanes.size() ; i++)
			{
				if(airplanes.at(i).alive)
				{
				x+=airplanes.at(i).x;
				y+=airplanes.at(i).y;
				}
			}
			return std::make_pair<f32,f32>(x/airplanes.size(),y/airplanes.size());
			// Get middle of planes
		}
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
				f32 tX = airplanes.at(i).x;
				f32 tY = airplanes.at(i).y;
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