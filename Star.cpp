#include "Star.h"
#include "Component.h"
#include "CameraState.h"
#include "PlayerState.h"
#include <memory>
#include <algorithm>

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

			Color starColors[] = {
				{150, 180, 255, 255}, // �Ķ� �� (�߰ſ�)
				{200, 220, 255, 255}, // ���� �Ķ�
				{255, 245, 235, 255}, // ��� (�¾� ���)
				{255, 255, 200, 255}, // ���� ���
				{255, 200, 150, 255}, // ��Ȳ��
				{255, 150, 100, 255}  // ���� �� (������)
			};
			effectComponent->color = starColors[Random::randColor(Random::gen)];

			transformComponent->size = Random::randSize(Random::gen);
			transformComponent->position = MyVector2{ randPosX(Random::gen), randPosY(Random::gen) };

			float sizeRatio = (transformComponent->size - MIN_STAR_SIZE) / (MAX_STAR_SIZE - MIN_STAR_SIZE);
			effectComponent->distanceDepth = 1.0f - sizeRatio;
			effectComponent->maxSize = transformComponent->size;
			effectComponent->distanceDepth = std::clamp(effectComponent->distanceDepth, 0.1f, 1.0f);

			renderComponent->points.push_back(transformComponent->position);
		}
	}

	void Star::Update()
	{
		auto* transformComponent = Object::GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);
		MyVector2& position = transformComponent->position;

		Move();

		Bound bound = CalculaterBoundLine();
		IsLineOut isLineOut = CheckCameraRangeOut(bound, position);
		
		SetRandomPosition(bound, isLineOut, position);
	}

	void Star::Move()
	{
		auto* moveComponent = Object::GetComponent<MoveComponent>(ComponentID::MOVE_COMPONENT);
		auto* effectComponent = Object::GetComponent<EffectComponent>(ComponentID::EFFECT_COMPONENT);
		
		if (moveComponent && effectComponent)
		{
			std::shared_ptr<Player> player = PlayerState::Instance().GetPlayer();

			const MyVector2& playerMoveDirection = player.get()->GetComponent<MoveComponent>(ComponentID::MOVE_COMPONENT)->direction;
			const float& playerSpeed = player.get()->GetComponent<MoveComponent>(ComponentID::MOVE_COMPONENT)->speed;

			const float& depth = effectComponent->distanceDepth;

			moveComponent->direction = playerMoveDirection;
			moveComponent->speed = playerSpeed * depth;
		}
	}

	Star::IsLineOut Star::CheckCameraRangeOut(Bound bound, const MyVector2& position)
	{
		float margin = 30.f;

		return IsLineOut{ position.x() <= bound.left - margin,
					position.x() >= bound.right + margin,
					position.y() <= bound.top - margin,
					position.y() >= bound.bottom + margin 
		};
	}

	Star::Bound Star::CalculaterBoundLine()
	{
		const Camera2D& camera = CameraState::Instance().GetCamera();
		const float& zoom = camera.zoom;
		const MyVector2& cameraTarget = camera.target;

		// ȭ�� ������ ���� �� üũ
		float viewHalfWidth = (SCREEN_WIDTH / zoom) / 2.f;
		float viewHalfHeight = (SCREEN_HEIGHT / zoom) / 2.f;

		float leftBound = cameraTarget.x() - viewHalfWidth;
		float rightBound = cameraTarget.x() + viewHalfWidth;
		float topBound = cameraTarget.y() - viewHalfHeight;
		float bottomBound = cameraTarget.y() + viewHalfHeight;

		return Bound{ leftBound, rightBound, topBound, bottomBound };
	}

	void Star::SetRandomPosition(Bound bound, IsLineOut isLineOut, MyVector2& position)
	{
		auto* renderComponent = Object::GetComponent<RenderComponent>(ComponentID::RENDER_COMPONENT);

		float margin = 100.f;
		Rectangle spotRange{ 0,0,0,0 };

		if (isLineOut.left)
		{
			spotRange = { bound.right, bound.top, margin, SCREEN_HEIGHT};
		}
		else if (isLineOut.right)
		{
			spotRange = { bound.left - margin, bound.top, margin, SCREEN_HEIGHT};
		}
		else if (isLineOut.top)
		{
			spotRange = { bound.left, bound.bottom, SCREEN_WIDTH, margin};
		}
		else if (isLineOut.bottom)
		{
			spotRange = { bound.left, bound.top - margin, SCREEN_WIDTH, margin};
		}

		if (isLineOut.left || isLineOut.right || isLineOut.top || isLineOut.bottom)
		{
			std::uniform_real_distribution<float> randPosX(spotRange.x, spotRange.x + spotRange.width);
			std::uniform_real_distribution<float> randPosY(spotRange.y, spotRange.y + spotRange.height);

			position = MyVector2{ randPosX(Random::gen), randPosY(Random::gen) };

			renderComponent->points[0] = position;
		}
	}
}
