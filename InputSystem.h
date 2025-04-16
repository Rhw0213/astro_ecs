#pragma once
#include "System.h"
#include "Component.h"
#include <vector> 

namespace astro
{
	class InputSystem : public System
	{
	public:
		void Process() override;

		/*
		void RegisterPressKey(size_t key)
		{
			if (key != 0)
			{
				pressedKeys.push_back(key);
			}
		}

		size_t IsRegisterPressKey(size_t key)
		{
			auto it = std::find(pressedKeys.begin(), pressedKeys.end(), key));
			if (it != pressedKeys.end())
			{
				return *it;
			}
			return 0;
		}

		void RegisterRemoveKey(size_t key)
		{
			auto it = std::find(pressedKeys.begin(), pressedKeys.end(), key));
			if (it != pressedKeys.end())
			{
				pressedKeys.erase(it);
			}
		}
		*/

	private:
		std::vector<size_t> pressedKeys;
	};
}
