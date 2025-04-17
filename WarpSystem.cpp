#include "WarpSystem.h"
#include "Component.h"
#include "EventManager.h"
#include "Event.h"
#include "PlayerState.h"

namespace astro
{
    void WarpSystem::Init()
    {
        for (const auto& object : objects)
        {
            EventManager::Instance().RegisterEvent<WarpStartEvent>([&](const WarpStartEvent* e)
                {
                    auto* renderComponent = object.get()->GetComponent<RenderComponent>(ComponentID::RENDER_COMPONENT);
                    auto* transformComponent = object.get()->GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);
                    auto& points = renderComponent->points;
                    float size = transformComponent->size;

                    MyVector2 effectDirection =
                        PlayerState::Instance()
                        .GetPlayer()
                        .get()->GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT)->direction;
                    float effectDistance = size * 30;
                    effectDirection *= -1.0f;

                    MyVector2 effectLine = effectDirection * effectDistance;
                    MyVector2 startPoint = transformComponent->position;
                    MyVector2 endPoint = startPoint + effectLine;

                    points.push_back(startPoint);
                    points.push_back(endPoint);
                }
            );
        }
    }

    void WarpSystem::Process()
	{
        for (const auto& object : objects)
        {
            auto* renderComponent = object.get()->GetComponent<RenderComponent>(ComponentID::RENDER_COMPONENT);
            auto& points = renderComponent->points;

            // 워프 꺼졌을때
            if (points.size() > 1)
            {
                float distance = points[1].Distance(points[2]);

                MyVector2 pointOneDirection = points[2].DirectionTo(points[1]);

                points[2] += (pointOneDirection * 2.f);

                if (distance < 3.f)
                {
                    const MyVector2& point = points[0];
                    points.clear();
                    points.push_back(point);
                }
            }
        }
	}
}
