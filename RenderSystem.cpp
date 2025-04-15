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
				size_t size = points.size();

				for (size_t i = 0; i < size; i++)
				{
					MyVector2& startPoint = points[i];
					MyVector2& endPoint = points[(i + 1) % size];

					DrawLine(static_cast<int>(startPoint.x()), 
								static_cast<int>((int)startPoint.y()), 
								static_cast<int>((int)endPoint.x()), 
								static_cast<int>((int)endPoint.y()), WHITE);
				}
			}
		}
		EndDrawing();
	}
}
