#pragma once
#include "GameObject.h"

namespace astro
{
	class Planet : public GameObject
	{
	public:
		Planet(const MyVector2& position);
		void Init() override;
		void Update() override;

		ObjectID GetID() const override { return ObjectID::PLANET_ID; };
	private:
	};
}
