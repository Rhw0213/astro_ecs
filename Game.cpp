#include "Game.h"
#include "Common.h"

namespace astro
{
	Game::Game()
		: player(MyVector2{ astro::SCREEN_WIDTH / 2.f, astro::SCREEN_HEIGHT / 2.f })
	{
	}
	void Game::Init()
	{
		player.Init();
	}
	void Game::Run()
	{
		player.Update();
	}
}
