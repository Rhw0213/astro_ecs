#pragma once
#include "System.h"
#include "Star.h"
#include <vector>
#include <memory>

namespace astro
{
	class StarEffectSystem : public System
	{
	public:
		StarEffectSystem() = default;
		void Process() override;

	public:
	};
}
