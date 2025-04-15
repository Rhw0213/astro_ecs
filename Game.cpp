#include "Game.h"
#include "Common.h"
#include "raylib.h"

namespace astro
{
	Game::Game()
	{
	}

	Game::~Game()
	{
		CloseWindow();
	}

	void Game::Init()
	{
		InitWindow(astro::SCREEN_WIDTH, astro::SCREEN_HEIGHT, "Game");
		SetTargetFPS(60);

		player = std::make_shared<Player>(MyVector2{ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
		player.get()->Init();

		renderSystem.RegisterComponent(player);
		moveSystem.RegisterComponent(player);
		inputSystem.RegisterComponent(player);
	}

	void Game::Run()
	{
		while (!WindowShouldClose())
		{
			player->Update();

			inputSystem.Process();
			moveSystem.Process();
			renderSystem.Process();
		}
	}
}
