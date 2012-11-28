#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "Types.h"
#include <vector>

namespace revel
{
	class AirPlane;
	class Bullet;
	class GameState
	{
		std::vector<AirPlane> airplanes;
		std::vector<Bullet> bullets;
	public:
		GameState();
		~GameState();

		std::pair<f32,f32> getCentre();

	};

	class AirPlane
	{
		f32 x; 
		f32 y;
		f32 angle;
		bool alive;

	public:
		AirPlane();
		~AirPlane();
	};

	class Bullet
	{
		f32 x; 
		f32 y;
		f32 angle;
		bool hit;

	public:
		Bullet();
		~Bullet();
	};

}
#endif