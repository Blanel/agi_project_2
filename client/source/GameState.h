#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "Types.h"
#include <vector>
#include <string>

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
		std::pair<std::pair<f32,f32>,std::pair<f32,f32>> GameState::getBoundingBox();

	};

	class AirPlane
	{
	public:
		f32 x; 
		f32 y;
		f32 angle;
		std::string name;
		bool alive;

		AirPlane();
		~AirPlane();
	};

	class Bullet
	{
	public:
		f32 x; 
		f32 y;
		f32 angle;
		bool hit;

		Bullet();
		~Bullet();
	};

}
#endif