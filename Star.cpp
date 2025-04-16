#include "Star.h"
#include "Component.h"
#include <memory>

namespace astro
{
	Star::Star(const MyVector2& position)
	{
		Object::AddComponent(std::make_shared<TransformComponent>(position));
		Object::AddComponent(std::make_shared<MoveComponent>());
		Object::AddComponent(std::make_shared<RenderComponent>());
		Object::AddComponent(std::make_shared<EffectComponent>());
	}

	void Star::Init()
	{
		auto* transformComponent = Object::GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);
		auto* renderComponent = Object::GetComponent<RenderComponent>(ComponentID::RENDER_COMPONENT);
		auto* effectComponent = Object::GetComponent<EffectComponent>(ComponentID::EFFECT_COMPONENT);

		if (renderComponent && transformComponent && effectComponent)
		{
			effectComponent->bright = Random::randBright(Random::gen);
			effectComponent->twinkle = Random::randTwinkle(Random::gen);
			transformComponent->size = Random::randSize(Random::gen);
			transformComponent->position = MyVector2{
				Random::randPosX(Random::gen),
				Random::randPosY(Random::gen),
			};

			renderComponent->points.push_back(transformComponent->position);
		}
	}

	void Star::Update()
	{
	}
}
