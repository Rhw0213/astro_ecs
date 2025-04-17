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
			transformComponent->size = Random::randSize(Random::gen);
			transformComponent->position = MyVector2{ randPosX(Random::gen), randPosY(Random::gen) };

			//effectComponent->distanceDepth = 1.f - (transformComponent->size / 3.f);
			float sizeRatio = (transformComponent->size - MIN_STAR_SIZE) / (MAX_STAR_SIZE - MIN_STAR_SIZE);
			effectComponent->distanceDepth = 1.0f - sizeRatio;
			effectComponent->maxSize = transformComponent->size;

			//// depth 값을 0.1 ~ 1.0 사이로 제한 (너무 가까운 별 방지)
			effectComponent->distanceDepth = std::clamp(effectComponent->distanceDepth, 0.1f, 1.0f);

			renderComponent->points.push_back(transformComponent->position);
		}
	}

	void Star::Update()
	{
		auto* transformComponent = Object::GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);
		auto* renderComponent = Object::GetComponent<RenderComponent>(ComponentID::RENDER_COMPONENT);
		auto* moveComponent = Object::GetComponent<MoveComponent>(ComponentID::MOVE_COMPONENT);
		auto* effectComponent = Object::GetComponent<EffectComponent>(ComponentID::EFFECT_COMPONENT);

		if (!transformComponent || !renderComponent) return;

		const Camera2D& camera = CameraState::Instance().GetCamera();
		const float& zoom = camera.zoom;
		const MyVector2& cameraTarget = camera.target;

		MyVector2& position = transformComponent->position;

		//별 이동
		std::shared_ptr<Player> player = PlayerState::Instance().GetPlayer();

		const MyVector2& playerMoveDirection = player.get()->GetComponent<MoveComponent>(ComponentID::MOVE_COMPONENT)->direction;
		const float& playerSpeed = player.get()->GetComponent<MoveComponent>(ComponentID::MOVE_COMPONENT)->speed;

		const float& depth = effectComponent->distanceDepth;

		moveComponent->direction = playerMoveDirection;
		moveComponent->speed = playerSpeed * depth;

		// 화면 밖으로 나간 별 체크
		float viewHalfWidth = (SCREEN_WIDTH / zoom) / 2.f;
		float viewHalfHeight = (SCREEN_HEIGHT / zoom) / 2.f;

		float leftBound = cameraTarget.x() - viewHalfWidth;
		float rightBound = cameraTarget.x() + viewHalfWidth;
		float topBound = cameraTarget.y() - viewHalfHeight;
		float bottomBound = cameraTarget.y() + viewHalfHeight;

		bool isLeftOut = position.x() <= leftBound - 30.f;
		bool isRightOut = position.x() >= rightBound + 30.f;
		bool isTopOut = position.y() <= topBound - 30.f;
		bool isBottomOut = position.y() >= bottomBound + 30.f;

		float margin = 100.f;
		Rectangle spotRange{ 0,0,0,0 };

		if (isLeftOut) 
		{ 
			spotRange = {rightBound, topBound, margin, viewHalfHeight * 2.f}; 
		}
		else if (isRightOut) 
		{ 
			spotRange = {leftBound - margin, topBound, margin, viewHalfHeight * 2.f }; 
		}
		else if (isTopOut) 
		{ 
			spotRange = { leftBound, bottomBound, viewHalfWidth * 2.f, margin };
		}
		else if (isBottomOut)
		{
			spotRange = { leftBound, topBound - margin, viewHalfWidth * 2.f, margin };
		}

		if (isLeftOut || isRightOut || isTopOut || isBottomOut)
		{
			std::uniform_real_distribution<float> randPosX(spotRange.x, spotRange.x + spotRange.width);
			std::uniform_real_distribution<float> randPosY(spotRange.y, spotRange.y + spotRange.height);

			position = MyVector2{ randPosX(Random::gen), randPosY(Random::gen) };
		}

		renderComponent->points[0] = position;
	}
}
