#include <iostream>
#include <vector>
#include <Windows.h>


#include "2DPhysicsObj.h"
#include "Physics.h"
#include "Timing.h"



namespace Physics
{
	float GetFrameTime()
	{
		static Timing::tick_t lastFrameStartTick = 0;

		float FrameTime;

		Timing::tick_t currentFrameStartTick = Timing::GetCurrentTickCounter();

		FrameTime = (lastFrameStartTick == 0) ? (1.0f / 60.0f) : (Timing::GetTimeDiff_ms(currentFrameStartTick, lastFrameStartTick) / 1000);

		lastFrameStartTick = currentFrameStartTick;

		return IsDebuggerPresent() ? (1.0f / 60.0f) : FrameTime;
	}

	void Update(TwoDPhysicsObj& obj, float dT, std::vector<Vector2>& forces)
	{
		float xForces = 0;
		float yForces = 0;
		float preXVelocity = obj.GetXVelocity();
		float preYVelocity = obj.GetYVelocity();

		for (std::vector<Vector2>::iterator fo = forces.begin(); fo != forces.end(); ++fo)
		{
			xForces += fo->x;
			yForces += fo->y;
		}

		obj.SetXAcceleration(xForces / obj.GetMass());
		obj.SetYAcceleration(yForces / obj.GetMass());

		obj.SetXVelocity(preXVelocity + obj.GetXAcceleration() * dT);
		obj.SetYVelocity(preYVelocity + obj.GetYAcceleration() * dT);

		obj.SetXPosition(obj.GetXPosition() + ((preXVelocity + obj.GetXVelocity()) / 2) * dT);
		obj.SetYPosition(obj.GetYPosition() + ((preYVelocity + obj.GetYVelocity()) / 2) * dT);

	}
}