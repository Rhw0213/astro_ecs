#include "Planet.h"
#include "Component.h"

namespace astro
{
	Planet::Planet(const MyVector2& position)
	{
		Object::AddComponent(std::make_shared<TransformComponent>(position));
		Object::AddComponent(std::make_shared<RenderComponent>());
		Object::AddComponent(std::make_shared<MoveComponent>());
	}

	void Planet::Init()
	{
		auto* renderComponent = Object::GetComponent<RenderComponent>(ComponentID::RENDER_COMPONENT);
		auto* transformComponent = Object::GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);
		auto* moveComponent = Object::GetComponent<MoveComponent>(ComponentID::MOVE_COMPONENT);

	}

	void Planet::Update()
	{
	}
}
