#pragma once
#include "System.h"
#include "Component.h"

namespace astro
{
	class InputSystem : public System
	{
	public:
		void Process() override;
	};
}
