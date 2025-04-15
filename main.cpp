#include <iostream>
#include "raylib.h"
#include "Game.h"
#include "Common.h"

int main()
{
	astro::Game game;
	game.Init();
	
	InitWindow(astro::SCREEN_WIDTH, astro::SCREEN_HEIGHT, "Game");
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		game.Run();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}