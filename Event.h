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
}
