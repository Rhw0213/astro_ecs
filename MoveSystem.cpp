#include "MoveSystem.h"

namespace astro
{
	void MoveSystem::Process()
	{
		for (const auto& object : objects)
		{
			if (object)
			{
				auto* transformComponent = 
					object.get()->GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);

				auto* moveComponent = 
					object.get()->GetComponent<MoveComponent>(ComponentID::MOVE_COMPONENT);

				if (transformComponent && moveComponent)
				{

					MyVector2& position = transformComponent->position;
					MyVector2& direction = transformComponent->direction;
					const MyVector2& moveDirection = moveComponent->direction;
					const float& speed = moveComponent->speed;
			
					direction += moveDirection;
					direction = direction.Normalize();

					position += (direction * speed);
				}
			}
		}
	}
}
