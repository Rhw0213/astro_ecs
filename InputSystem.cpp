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
				auto* cameraComponent = object.get()->GetComponent<CameraComponent>(ComponentID::CAMERA_COMPONENT);

				MyVector2& position = transformComponent->position;
				MyVector2& direction = transformComponent->direction;
				MyVector2& moveDirection = moveComponent->direction;
				float& moveSpeed = moveComponent->speed;

				const Camera2D& camera = cameraComponent->camera;
			
				const MyVector2& mousePosition = GetScreenToWorld2D(GetMousePosition(), camera);

				if (!IsKeyDown(KEY_SPACE))
				{
					direction = position.DirectionTo(mousePosition);
				}

				if (moveComponent)
				{
					MyVector2 move = { 0, 0 };
					float speed = 0.f;

					if (IsKeyDown(KEY_W))
					{
						speed = 500.f;
						move += { direction.x(), direction.y() };

						if (IsKeyDown(KEY_SPACE))
						{
							speed = 1500.f;
						}
					}

					if (IsKeyDown(KEY_A))
					{
						speed = 300.f;
						move += { direction.y(), -direction.x() };
					}

					if (IsKeyDown(KEY_D))
					{
						speed = 300.f;
						move += { -direction.y(), direction.x() };
					}

					if (IsKeyDown(KEY_S))
					{
						speed = 300.f;
						move += { -direction.x(), -direction.y() };
					}
					
					moveDirection = move;
					moveSpeed = speed;
				}
			}
		}
	}
}
