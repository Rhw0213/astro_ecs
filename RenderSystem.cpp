#include "RenderSystem.h"

namespace astro
{
	void RenderSystem::Process()
	{
		BeginDrawing();
		ClearBackground(BLACK);

		for (const auto& object: objects)
		{
			if (object)
			{
				auto& points = object.get()->GetComponent<RenderComponent>(ComponentID::RENDER_COMPONENT)->points;
				auto* transform = object.get()->GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);

				MyVector2& direction = transform->direction;
				MyVector2& position = transform->position;

				size_t size = points.size();

				if (object->GetID() != ObjectID::STAR_ID)
				{
					for (size_t i = 0; i < size; i++)
					{
						MyVector2& startPoint = points[i];
						MyVector2& endPoint = points[(i + 1) % size];

						DrawLine(static_cast<int>(startPoint.x()),
							static_cast<int>(startPoint.y()),
							static_cast<int>(endPoint.x()),
							static_cast<int>(endPoint.y()), WHITE);

					}

					MyVector2 endPoint = position + direction * 100;

					DrawLine(static_cast<int>(position.x()),
						static_cast<int>(position.y()),
						static_cast<int>(endPoint.x()),
						static_cast<int>(endPoint.y()), YELLOW);
				}
				else
				{
					auto* effectComponent = object.get()->GetComponent<EffectComponent>(ComponentID::EFFECT_COMPONENT);
					size_t bright = effectComponent->bright;

					for (const auto& point : points)
					{
						DrawCircle(static_cast<int>(point.x()), 
									static_cast<int>(point.y()), transform->size, {255,255,255,(unsigned char)bright});
					}
				}
			}
		}

		EndDrawing();
	}
}
