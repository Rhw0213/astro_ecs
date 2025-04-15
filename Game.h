#pragma once
#include "Player.h"

namespace astro
{

	class Game
	{
	public:
		Game();
		~Game() = default;
		void Init();
		void Run();

	private:
		Player player;
	};
}
