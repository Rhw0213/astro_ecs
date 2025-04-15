#include "Player.h"
#include "Component.h"
#include <cmath> 

namespace astro
{
	Player::Player(const MyVector2& position)
	{
		Object::AddComponent(new TransformComponent(position));
		Object::AddComponent(new RenderComponent());
	}

	void Player::Init()
	{
		auto* render = Object::GetComponent<RenderComponent>(ComponentID::RENDER_COMPONENT);
		auto* transform = Object::GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);

		if (transform && render)
		{
			transform->direction = { 0, -1 };
			transform->size = 50;
			render->points.reserve(3);
		}
	}

	void Player::Update()
	{
		CalculationTransform();
	}

	void Player::CalculationTransform()
	{
		//  수학적 계산
		//	direction 벡터의 각도를 구합니다 : θ = atan2(direction.y, direction.x).
		//	정삼각형의 세 꼭지점은 중심(0, 0)에서 다음 각도로 위치 :
		//  꼭지점 1 : θ(방향 기준)
		//	꼭지점 2 : θ + 120°
		//	꼭지점 3 : θ + 240°
		//	각 꼭지점의 좌표 :
		//  (r * cos(θ), r * sin(θ))
		//	(r * cos(θ + 120°), r * sin(θ + 120°))
		//	(r * cos(θ + 240°), r * sin(θ + 240°))
		//	최종적으로 position을 더해 이동 : (x + position.x, y + position.y).
		auto* transform = Object::GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);
		auto* render = Object::GetComponent<RenderComponent>(ComponentID::RENDER_COMPONENT);
		if (transform && render)
		{
			auto direction = transform->direction.Normalize();
			auto& position = transform->position;
			auto& points = render->points;
			float size = transform->size;
			float angle = atan2f(direction.y(), direction.x());

			points.clear();

			const float deg_to_rad = PI / 180.0f;

			points.push_back(position + MyVector2{ size * std::cosf(angle), size * std::sinf(angle) });
			points.push_back(position + MyVector2{ size * std::cosf(angle + 120.0f * deg_to_rad), size * std::sinf(angle + 120.0f * deg_to_rad) });
			points.push_back(position + MyVector2{ size * std::cosf(angle + 240.0f * deg_to_rad), size * std::sinf(angle + 240.0f * deg_to_rad) });

			//DrawTriangle(points[0], points[2], points[1], BLACK);
			DrawTriangleLines(points[0], points[2], points[1], WHITE);
		}

	}
}
