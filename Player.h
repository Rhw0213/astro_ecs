#pragma once
#include "GameObject.h"

namespace astro
{
	class Player : public GameObject
	{
	public:
		Player(const MyVector2& position = {0, 0});

		void Init() override;
		void Update() override;
		void CalculationTransform();
	private:
	};
}
