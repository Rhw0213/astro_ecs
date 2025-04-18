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
				auto* transformComponent = object.get()->GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);

				const MyVector2& direction = transformComponent->direction;
				const MyVector2& position = transformComponent->position;
				const float& size = transformComponent->size;

				size_t pointsSize = points.size();

				if (object->GetID() == ObjectID::STAR_ID)
				{
					auto* effectComponent = object.get()->GetComponent<EffectComponent>(ComponentID::EFFECT_COMPONENT);
					size_t bright = effectComponent->bright;
					Color starColor = effectComponent->color;
					enum DrawIndex
					{
						CIRCLE,
						LINE
					};

					pointsSize = pointsSize == 1 ? 1 : pointsSize - 1;

					for (size_t i = 0; i < pointsSize; i++)
					{
						if (i == CIRCLE)
						{
							MyVector2 renderPosition = points[CIRCLE];
							DrawCircle(static_cast<int>(renderPosition.x()),
										static_cast<int>(renderPosition.y()), 
										size, 
										{ starColor.r, starColor.g, starColor.b, (unsigned char)bright });
						}
						else if (i == LINE)
						{
							DrawLine(static_cast<int>(points[i].x()),
								static_cast<int>(points[i].y()),
								static_cast<int>(points[i + 1].x()),
								static_cast<int>(points[i + 1].y()), starColor);
						}
					}

				}
				else if (object.get()->GetID() == ObjectID::PLAYER_ID)
				{
					for (size_t i = 0; i < pointsSize; i++)
					{
						MyVector2& startPoint = points[i];
						MyVector2& endPoint = points[(i + 1) % pointsSize];

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
				else if (object.get()->GetID() == ObjectID::ASTEROID_ID)
				{
					if (pointsSize > 3)
					{
						for (size_t i = 0; i < pointsSize - 1; i++) {
							DrawLineEx(points[i], points[i + 1], 1.0f, WHITE);
						}
						DrawLineEx(points.back(), points[0], 1.0f, WHITE);
					}
					MyVector2 endPoint = position + direction * 50;

					DrawLine(static_cast<int>(position.x()),
						static_cast<int>(position.y()),
						static_cast<int>(endPoint.x()),
						static_cast<int>(endPoint.y()), RED);
				}
			}
		}

		EndMode2D();
		EndDrawing();
	}
}
