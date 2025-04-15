#include "InputSystem.h"
#include "raylib.h"

namespace astro
{
	void InputSystem::Process()
	{
		for (const auto& object: objects)
		{
			if (object && object.get()->GetID() == ObjectID::PLAYER_ID)
			{
				size_t key = GetKeyPressed();
				
				if (key > 0)
				{
					auto* moveComponent = object.get()->GetComponent<MoveComponent>(ComponentID::MOVE_COMPONENT);

					if (moveComponent)
					{
						moveComponent->speed = 1.f;

						if (key == KEY_W)
						{
							moveComponent->direction = { 0, -1 };
						}
						else if (key == KEY_A)
						{
							moveComponent->direction = { -1, 0 };
						}
						else if (key == KEY_D)
						{
							moveComponent->direction = { 1, 0 };
						}
						else if (key == KEY_S)
						{
							moveComponent->direction = { 0, 1 };
						}
					}
				}
			}
		}
	}
}
