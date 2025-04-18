#include "SystemManager.h"
#include "CameraSystem.h"
#include "InputSystem.h"
#include "MoveSystem.h"
#include "RenderSystem.h"
#include "RotationSystem.h"
#include "StarEffectSystem.h"
#include "WarpSystem.h"

namespace astro
{
	SystemManager::SystemManager()
	{
		RegisterSystem<InputSystem>(std::make_shared<InputSystem>());
		RegisterSystem<CameraSystem>(std::make_shared<CameraSystem>());
		RegisterSystem<MoveSystem>(std::make_shared<MoveSystem>());
		RegisterSystem<StarEffectSystem>(std::make_shared<StarEffectSystem>());
		RegisterSystem<RenderSystem>(std::make_shared<RenderSystem>());
		RegisterSystem<WarpSystem>(std::make_shared<WarpSystem>());
		RegisterSystem<RotationSystem>(std::make_shared<RotationSystem>());
	}

	void SystemManager::Init()
	{
		for (const auto& system : systems)
		{
			system.get()->Init();
		}
	}

	void SystemManager::RunProcess()
	{
		for (const auto& system : systems)
		{
			system.get()->Process();
		}
	}
}
