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

		// STAR
		starManager = std::make_unique<ObjectManager>();
		for (int i = 0; i < 200; i++)
		{
			std::shared_ptr<Star> star = starManager->CreateObject<Star>();
			effectSystem.RegisterObject(star);
			moveSystem.RegisterObject(star);
			renderSystem.RegisterObject(star);
		}
		starManager->Init();

        //for (int i = 0; i < 200; i++)
        //{
        //    std::shared_ptr<Star> star = std::make_shared<Star>(
        //        MyVector2
		//		{
		//			backgroundSystem.randPosX(backgroundSystem.gen), 
		//			backgroundSystem.randPosY(backgroundSystem.gen)
		//		},
        //        backgroundSystem.randBright(backgroundSystem.gen),
        //        backgroundSystem.randTwinkle(backgroundSystem.gen),
		//		backgroundSystem.randSize(backgroundSystem.gen)
        //    );
		//	star.get()->Init();
		//	renderSystem.RegisterObject(star);
		//	moveSystem.RegisterObject(star);
        //}

	}

	void Game::Run()
	{
		while (!WindowShouldClose())
		{
			player->Update();
			starManager->Update();

			inputSystem.Process();
			moveSystem.Process();
			effectSystem.Process();
			renderSystem.Process();
		}
	}
}
