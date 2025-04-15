#include "Player.h"
#include "Component.h"
#include <cmath> 
#include <memory> 

namespace astro
{
	Player::Player(const MyVector2& position)
	{
		Object::AddComponent(std::make_shared<TransformComponent>(position));
		Object::AddComponent(std::make_shared<RenderComponent>());
		Object::AddComponent(std::make_shared<InputComponent>());
		Object::AddComponent(std::make_shared<MoveComponent>(MyVector2{0.f, 0.f}, 0.f));
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
		//  ������ ���
		//	direction ������ ������ ���մϴ� : �� = atan2(direction.y, direction.x).
		//	���ﰢ���� �� �������� �߽�(0, 0)���� ���� ������ ��ġ :
		//  ������ 1 : ��(���� ����)
		//	������ 2 : �� + 120��
		//	������ 3 : �� + 240��
		//	�� �������� ��ǥ :
		//  (r * cos(��), r * sin(��))
		//	(r * cos(�� + 120��), r * sin(�� + 120��))
		//	(r * cos(�� + 240��), r * sin(�� + 240��))
		//	���������� position�� ���� �̵� : (x + position.x, y + position.y).
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
		}

	}
}
