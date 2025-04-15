#pragma once
#include <vector>
#include <memory>
#include "Component.h"
#include "Common.h"

namespace astro
{
	class Object
	{
	public:
		Object() = default;
		virtual ~Object() = default;

		void AddComponent(Component* comp)
		{
			for (const auto& component : components)
			{
				if (comp->GetID() == component->GetID())
				{
					return;
				}
			}

			components.push_back(std::unique_ptr<Component>(comp));
		}

		template <typename T>
		T* GetComponent(ComponentID id)
		{
			for (const auto& component : components)
			{
				if (component->GetID() == id)
				{
					return static_cast<T*>(component.get());
					break;
				}
			}

			return nullptr;
		}

	private:
		std::vector<std::unique_ptr<Component>> components;
	};
}
