#pragma once
#include "Common.h"
#include <vector> 

namespace astro
{
	class Component 
	{ 
	public:
		virtual ComponentID GetID() = 0;
		virtual ~Component() = default; 
	};

	struct TransformComponent : public Component
	{
		TransformComponent(const MyVector2& position = {0, 0}, const MyVector2& direction = {0, 0}, const float& size = 1.f)
			: position(position)
			, direction(direction)
			, size(size)
		{ }

		ComponentID GetID() override 
		{ 
			return ComponentID::TRANSFORM_COMPONENT;
		}

		MyVector2 position{ 0, 0 };
		MyVector2 direction{ 0, 0 };
		float size = 0;
	};

	struct RenderComponent : public Component
	{
		RenderComponent() { }

		ComponentID GetID() override 
		{ 
			return ComponentID::RENDER_COMPONENT;
		}

		std::vector<MyVector2> points;
	};

	struct InputComponent : public Component
	{
		InputComponent() { }

		ComponentID GetID() override 
		{ 
			return ComponentID::INPUT_COMPONENT;
		}
	};

	struct MoveComponent : public Component
	{
		MoveComponent(const MyVector2& direction = {0, 0}, const float& speed = 0.f)
			: direction(direction)
			, speed(speed)
		{ }

		ComponentID GetID() override 
		{ 
			return ComponentID::MOVE_COMPONENT;
		}

		MyVector2 direction{ 0, 0 };
		float speed = 0.f;
	};
}
