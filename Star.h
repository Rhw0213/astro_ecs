#pragma once
#include "GameObject.h"

namespace astro
{
	class Star : public GameObject
	{
	public:
		Star(const MyVector2& position = {0, 0});
		ObjectID GetID() const override { return ObjectID::STAR_ID; };
		void Init() override;
		void Update() override;

	private:
	};
}
