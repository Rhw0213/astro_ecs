#include "EffectSystem.h"
#include "Component.h"

namespace astro
{
    void EffectSystem::Process()
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

                time += GetFrameTime() * twinkle;
                size = 1.f + 0.8f * sinf(time);
                //bright = 100 + 155 * (sinf(time) + 1) / 2;
                bright = 127 + 127 * sinf(time);

            }
        }
    }
}
