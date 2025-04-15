#pragma once
#include "Component.h"
#include "System.h"

namespace astro
{
	class RenderSystem : public System
	{
	public:
		void Process() override;
	};
}
