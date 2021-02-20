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

	void Update(TwoDPhysicsObj& obj, std::vector<Vector2>& forces, float dT)
	{
		float xForces = 0;
		float yForces = 0;
		float preXVelocity = obj.posAndVec.getXVector();
		float preYVelocity = obj.posAndVec.getYVector();

		for (std::vector<Vector2>::iterator fo = forces.begin(); fo != forces.end(); ++fo)
		{
			xForces += fo->x;
			yForces += fo->y;
		}

		obj.SetXAcceleration(xForces / obj.GetMass());
		obj.SetYAcceleration(yForces / obj.GetMass());

		obj.posAndVec.setXVector(preXVelocity + obj.GetXAcceleration() * dT);
		obj.posAndVec.setYVector(preYVelocity + obj.GetYAcceleration() * dT);

		obj.posAndVec.setXPosition(obj.posAndVec.getXPosition() + ((preXVelocity + obj.posAndVec.getXVector()) / 2) * dT);
		obj.posAndVec.setYPosition(obj.posAndVec.getYPosition() + ((preYVelocity + obj.posAndVec.getYVector()) / 2) * dT);

	}
}