#pragma once
#include "Player.h"
#include "RenderSystem.h"
#include "MoveSystem.h"
#include "InputSystem.h"
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
		RenderSystem renderSystem;
		MoveSystem moveSystem;
		InputSystem inputSystem;
	};
}
