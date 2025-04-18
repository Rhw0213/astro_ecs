#include "CameraSystem.h"
#include "CameraState.h"
#include "Component.h"
#include "EventManager.h"

namespace astro
{
	void CameraSystem::Init()
	{
		for (const auto& object : objects)
		{
			if (object)
			{
				EventManager::Instance().RegisterEvent<CameraZoomEvent>([&](const CameraZoomEvent* e) {
					auto* cameraComponent = object.get()->GetComponent<CameraComponent>(ComponentID::CAMERA_COMPONENT);
					Camera2D& camera = cameraComponent->camera;

					camera.zoom = e->zoom;
				});
			}
		}
	}
	void CameraSystem::Process()
	{
		for (const auto& object : objects)
		{
			if (object)
			{
				auto* cameraComponent = object.get()->GetComponent<CameraComponent>(ComponentID::CAMERA_COMPONENT);
				auto* transformComponent = object.get()->GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);

				Camera2D& camera = cameraComponent->camera;
				const MyVector2& position = transformComponent->position;

				camera.target = position;

				CameraState::Instance().Update(camera);
			}
		}
	}
}
