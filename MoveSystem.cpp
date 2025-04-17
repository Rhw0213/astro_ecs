#include "MoveSystem.h"

namespace astro
{
	void MoveSystem::Init()
	{
	}

	void MoveSystem::Process()
	{
		for (const auto& object : objects)
		{
			auto* transformComponent = object.get()->GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);
			auto* moveComponent = object.get()->GetComponent<MoveComponent>(ComponentID::MOVE_COMPONENT);

			if (object)
			{
				if (transformComponent && moveComponent)
				{
					MyVector2& position = transformComponent->position;
					const MyVector2& moveDirection = moveComponent->direction.Normalize();
					const float& speed = moveComponent->speed;
					MyVector2& slowVelocity = moveComponent->slowVelocity;
					
					if (speed <= 0.1f)
					{
						slowVelocity *= 0.95f;
					}
					else
					{
						slowVelocity = moveDirection * speed * GetFrameTime();
					}

					position += slowVelocity;
				}
			}
		}
	}
}
