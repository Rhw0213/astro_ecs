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
		MoveComponent(const MyVector2& direction = { 0, 0 }, const float& speed = 0.f, const MyVector2& slowVelocity = { 0, 0 })
			: direction(direction)
			, speed(speed)
			, slowVelocity(slowVelocity)
		{ }

		ComponentID GetID() override 
		{ 
			return ComponentID::MOVE_COMPONENT;
		}

		MyVector2 direction{ 0, 0 };
		MyVector2 slowVelocity{ 0, 0 };
		float speed = 0.f;
	};

	struct EffectComponent : public Component
	{
		EffectComponent(int bright = 0.f, float twinkle = 0.f)
			: bright(bright)
			, twinkle(twinkle)
			, time(0.f)
		{ }

		ComponentID GetID() override 
		{ 
			return ComponentID::EFFECT_COMPONENT;
		}

		int bright = 0;
		float twinkle = 0.f;
		float time = 0.f;
	};
}
