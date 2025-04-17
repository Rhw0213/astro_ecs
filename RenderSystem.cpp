#include "RenderSystem.h"
#include "CameraState.h"

namespace astro
{
	void RenderSystem::Init()
	{
	}

	void RenderSystem::Process()
	{
		BeginDrawing();
		ClearBackground(BLACK);

		for (const auto& object: objects)
		{
			//Camera
			auto* cameraComponent = object.get()->GetComponent<CameraComponent>(ComponentID::CAMERA_COMPONENT);
			if (cameraComponent)
			{
				Camera2D& camera = cameraComponent->camera;
				BeginMode2D(camera);
			}

			//Object
			if (object)
			{
				auto& points = object.get()->GetComponent<RenderComponent>(ComponentID::RENDER_COMPONENT)->points;
				auto* transform = object.get()->GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);

				MyVector2& direction = transform->direction;
				MyVector2& position = transform->position;

				size_t size = points.size();

				if (object->GetID() == ObjectID::STAR_ID)
				{
					auto* effectComponent = object.get()->GetComponent<EffectComponent>(ComponentID::EFFECT_COMPONENT);
					size_t bright = effectComponent->bright;

					enum DrawIndex
					{
						CIRCLE,
						LINE
					};

					size_t pointsSize = points.size() == 1 ? 1 : points.size() - 1;

					for (size_t i = 0; i < pointsSize; i++)
					{
						if (i == CIRCLE)
						{
							MyVector2 renderPosition = points[CIRCLE];

							DrawCircle(static_cast<int>(renderPosition.x()),
										static_cast<int>(renderPosition.y()), 
										transform->size, 
										{ 255,255,255,(unsigned char)bright });
						}
						else if (i == LINE)
						{
							DrawLine(static_cast<int>(points[i].x()),
								static_cast<int>(points[i].y()),
								static_cast<int>(points[i + 1].x()),
								static_cast<int>(points[i + 1].y()), WHITE);
						}
					}

				}
				else
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
			}
		}

		EndMode2D();
		EndDrawing();
	}
}
