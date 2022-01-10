#include "Timing.h"

#include <Windows.h>

#include <cassert>

namespace Timing
{
	unsigned int LastFrame_ms;
	static LARGE_INTEGER PerformanceFreq = { 0 };

	bool Int()
	{
		bool success = QueryPerformanceFrequency(&PerformanceFreq);
		assert(success);
		return success;
	}

	tick_t GetCurrentTickCounter() 
	{
		LARGE_INTEGER CurrentFrameCounter;

		bool success = QueryPerformanceCounter(&CurrentFrameCounter);
		assert(success);

		return CurrentFrameCounter.QuadPart;
	}

	float GetTimeDiff_ms(tick_t start, tick_t end)
	{
		assert(PerformanceFreq.QuadPart != 0);
		return(1000.0f * static_cast<float>(end - start)) / PerformanceFreq.QuadPart;
	}


}