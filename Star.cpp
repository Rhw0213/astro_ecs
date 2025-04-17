#include "Star.h"
#include "Component.h"
#include "CameraState.h"
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
			std::uniform_real_distribution<float> randPosX(0.f, astro::SCREEN_WIDTH);
			std::uniform_real_distribution<float> randPosY(0.f, astro::SCREEN_HEIGHT);

			effectComponent->bright = Random::randBright(Random::gen);
			effectComponent->twinkle = Random::randTwinkle(Random::gen);
			transformComponent->size = Random::randSize(Random::gen);
			transformComponent->position = MyVector2{ randPosX(Random::gen), randPosY(Random::gen) };

			renderComponent->points.push_back(transformComponent->position);
		}
	}

	void Star::Update()
	{
		auto* transformComponent = Object::GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);
		auto* renderComponent = Object::GetComponent<RenderComponent>(ComponentID::RENDER_COMPONENT);

		MyVector2& position = transformComponent->position;

		const Camera2D& camera = CameraState::Instance().GetCamera();
		MyVector2 target = camera.target;
		float x = target.x() - camera.offset.x;
		float y = target.y() - camera.offset.y;

		Rectangle view = Rectangle{ x, y, camera.offset.x * 2.f, camera.offset.y * 2.f};

		if (position.x() < view.x ||
			position.y() < view.y ||
			position.x() > view.x + view.width ||
			position.y() > view.y + view.height)
		{
			float offset = 100.f;
			std::uniform_real_distribution<float> randPosX(view.x - offset, view.x + view.width + offset);
			std::uniform_real_distribution<float> randPosY(view.y - offset, view.y + view.height + offset);

			position = MyVector2{ randPosX(Random::gen), randPosY(Random::gen) };

			renderComponent->points.clear();
			renderComponent->points.push_back(position);
		}
	}
}
