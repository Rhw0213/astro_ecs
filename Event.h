#pragma once

namespace astro
{
	struct Event
	{
		virtual ~Event() = default;
	};

	struct WarpStartEvent : Event
	{
		WarpStartEvent() {};
	};

	struct WarpStopEvent : Event
	{
		WarpStopEvent() {};
	};

	struct CameraZoomEvent : Event
	{
		CameraZoomEvent(float zoom) : zoom(zoom) {};

		float zoom = 0.f;
	};
}
