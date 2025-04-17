#include "StarEffectSystem.h"
#include "Component.h"
#include "PlayerState.h"

namespace astro
{
    void StarEffectSystem::Process()
    {
        if (IsKeyDown(KEY_SPACE) && IsKeyDown(KEY_W))
        {
            isWarp = true;
        }
        else
        {
            isWarp = false;
        }

        for (const auto& object : objects)
        {
            if (object)
            {

                auto* effectComponent = object.get()->GetComponent<EffectComponent>(ComponentID::EFFECT_COMPONENT);
                auto* transformComponent = object.get()->GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);

                int& bright = effectComponent->bright;
                float& twinkle = effectComponent->twinkle;
                float& time = effectComponent->time;
                float& size = transformComponent->size;
                float maxSize = effectComponent->maxSize;

                // 반짝이는 효과(함수 전환 예정)
                time += GetFrameTime() * twinkle;
                size = maxSize * ((sinf(time) * 0.5f) + 0.5f);
                bright = 127 + 127 * sinf(time);

                // 스페이스 눌렀을때 워프효과(함수 전환 예정)
                auto* renderComponent = object.get()->GetComponent<RenderComponent>(ComponentID::RENDER_COMPONENT);
                auto& points = renderComponent->points;

                if (isWarp && points.size() == 1)
                {
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

                // 워프 꺼졌을때(함수전환예정)
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
}
