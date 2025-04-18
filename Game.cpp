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

		//Manager
		starManager = std::make_unique<ObjectManager>();
		systemManager = std::make_unique<SystemManager>();

		// PLAYER
		player = std::make_shared<Player>(MyVector2{ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
		player.get()->Init();

		systemManager.get()->RegisterObjectOfSystem(
			{	
				SystemManager::RENDER_SYSTEM,
				SystemManager::MOVE_SYSTEM,
				SystemManager::INPUT_SYSTEM,
				SystemManager::CAMERA_SYSTEM,
				SystemManager::ROTATION_SYSTEM,
			}, player);

		// STAR
		for (size_t i = 0; i < 200; i++)
		{
			std::shared_ptr<Star> star = starManager->CreateObject<Star>();

			systemManager.get()->RegisterObjectOfSystem(
				{	
					SystemManager::RENDER_SYSTEM,
					SystemManager::MOVE_SYSTEM,
					SystemManager::STAR_EFFECT_SYSTEM,
					SystemManager::WARP_SYSTEM,
			}, star);
		}
		starManager->Init();

		//Asteroid
		asteroid = std::make_shared<Asteroid>(MyVector2{ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
		systemManager.get()->RegisterObjectOfSystem(
			{	
					SystemManager::RENDER_SYSTEM,
					SystemManager::MOVE_SYSTEM,
					SystemManager::ROTATION_SYSTEM
		}, asteroid);
		asteroid->Init();

		systemManager->Init();
	}

	void Game::Run()
	{
		while (!WindowShouldClose())
		{
			systemManager->RunProcess();
			player->Update();
			starManager->Update();
			asteroid->Update();
		}
	}
}
