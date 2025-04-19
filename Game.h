#pragma once
#include "Player.h"
#include "Star.h"
#include "Asteroid.h"
#include "ObjectManager.h"
#include "SystemManager.h"
#include <memory> 

namespace astro
{
	class Game
	{
	public:
		Game();
		~Game();
		void Init();
		void Run();

	private:
		std::shared_ptr<Player> player;

		std::unique_ptr<ObjectManager> starManager;
		std::unique_ptr<ObjectManager> asteroidManager;

		std::unique_ptr<SystemManager> systemManager;
	};
}
