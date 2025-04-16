#pragma once
#include "Player.h"
#include "Star.h"
#include "RenderSystem.h"
#include "MoveSystem.h"
#include "InputSystem.h"
#include "EffectSystem.h"
#include "ObjectManager.h"
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

		RenderSystem renderSystem;
		MoveSystem moveSystem;
		InputSystem inputSystem;
		EffectSystem effectSystem;
	};
}
