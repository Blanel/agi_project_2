#include "GameState.h"

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
		return std::make_pair<f32,f32>(0,0);
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