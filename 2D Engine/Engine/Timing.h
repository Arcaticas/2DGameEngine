#pragma once
#include <cstdint>

namespace Timing
{
	typedef uint64_t tick_t;

	bool Int();
	tick_t GetCurrentTickCounter();
	float GetTimeDiff_ms(tick_t start, tick_t end = GetCurrentTickCounter());

}