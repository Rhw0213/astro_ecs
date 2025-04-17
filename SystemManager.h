#pragma once
#include <vector>
#include <memory>
#include <initializer_list>
#include "System.h" 

namespace astro
{
	class SystemManager
	{
	public:
		SystemManager();
		~SystemManager() = default;
	public:
		enum SystemID
		{
			INPUT_SYSTEM,
			CAMERA_SYSTEM,
			MOVE_SYSTEM,
			STAR_EFFECT_SYSTEM,
			RENDER_SYSTEM,
			WARP_SYSTEM
		};

		template <typename T>
		void RegisterObjectOfSystem(std::initializer_list<SystemID> ids, std::shared_ptr<T> ptr)
		{
			for (const auto& id : ids)
			{
				systems[id].get()->RegisterObject(ptr);
			}
		}

		void Init();
		void RunProcess();

	private:
		template <typename T>
		void RegisterSystem(std::shared_ptr<T> ptr)
		{
			systems.push_back(ptr);
		}

	private:
		std::vector<std::shared_ptr<System>> systems;
	};
}
