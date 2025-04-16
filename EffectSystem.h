#pragma once
#include "System.h"
#include "Star.h"
#include <vector>
#include <memory>

namespace astro
{
	class EffectSystem : public System
	{
	public:
		EffectSystem() = default;
		void Process() override;

	public:
	};
}
