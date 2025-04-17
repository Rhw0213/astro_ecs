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

		// PLAYER
		player = std::make_shared<Player>(MyVector2{ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
		player.get()->Init();
		renderSystem.RegisterObject(player);
		moveSystem.RegisterObject(player);
		inputSystem.RegisterObject(player);
		cameraSystem.RegisterObject(player);

		// STAR
		starManager = std::make_unique<ObjectManager>();
		for (int i = 0; i < 200; i++)
		{
			std::shared_ptr<Star> star = starManager->CreateObject<Star>();
			starEffectSystem.RegisterObject(star);
			moveSystem.RegisterObject(star);
			renderSystem.RegisterObject(star);
		}
		starManager->Init();
	}

	void Game::Run()
	{
		while (!WindowShouldClose())
		{
			inputSystem.Process();
			moveSystem.Process();
			starEffectSystem.Process();
			cameraSystem.Process();
			renderSystem.Process();

			player->Update();
			starManager->Update();
		}
	}
}
