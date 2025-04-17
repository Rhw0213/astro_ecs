#include "StarEffectSystem.h"
#include "Component.h"
#include "PlayerState.h"

namespace astro
{
    void StarEffectSystem::Init()
    {
    }

    void StarEffectSystem::Process()
    {
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

                // ��¦�̴� ȿ��
                time += GetFrameTime() * twinkle;
                size = maxSize * ((sinf(time) * 0.5f) + 0.5f);
                bright = 127 + 127 * sinf(time);
            }
        }
    }
}
