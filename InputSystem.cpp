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
				auto* moveComponent = object.get()->GetComponent<MoveComponent>(ComponentID::MOVE_COMPONENT);
				auto* transformComponent = object.get()->GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);

				MyVector2& position = transformComponent->position;
				MyVector2& direction = transformComponent->direction;
				MyVector2& moveDirection = moveComponent->direction;
			
				const MyVector2& mousePosition = GetMousePosition();
				direction = position.DirectionTo(mousePosition);

				if (moveComponent)
				{
					MyVector2 move = { 0, 0 };
					moveComponent->speed = 0.f;

					if (IsKeyDown(KEY_W))
					{
						moveComponent->speed = 500.f;
						move += { direction.x(), direction.y() };
					}

					if (IsKeyDown(KEY_A))
					{
						moveComponent->speed = 300.f;
						move += { direction.y(), -direction.x() };
					}

					if (IsKeyDown(KEY_D))
					{
						moveComponent->speed = 300.f;
						move += { -direction.y(), direction.x() };
					}

					if (IsKeyDown(KEY_S))
					{
						moveComponent->speed = 200.f;
						move += { -direction.x(), -direction.y() };
					}
					 
					moveDirection = move;
				}
			}
		}
	}
}
