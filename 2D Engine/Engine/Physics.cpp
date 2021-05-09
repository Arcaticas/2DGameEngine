#include <iostream>
#include <Windows.h>

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

	GameObjectOwner<TwoDPhysicsObj> CreatePhysicsObject(const float i_xPos,const float i_yPos)
	{
		TwoDPhysicsObj* temp = new TwoDPhysicsObj(i_xPos, i_yPos);
		AllPhysicsObjects.push_back(temp);
		return GameObjectOwner<TwoDPhysicsObj>(temp);
	}


	void Update(TwoDPhysicsObj& obj, std::vector<Point2D>& forces, float dT)
	{
		float xForces = 0;
		float yForces = 0;
		float preXVelocity = obj.posAndVec.getXVector();
		float preYVelocity = obj.posAndVec.getYVector();

		if (preXVelocity != 0 || preYVelocity != 0)
		{
			if (preXVelocity > 0)
			{
				xForces += -1 * obj.GetDragCoefficient() * preXVelocity * preXVelocity;
			}
			else
			{
				xForces += 1 * obj.GetDragCoefficient() * preXVelocity * preXVelocity;
			}
			if (preYVelocity > 0)
			{
				yForces += -1 * obj.GetDragCoefficient() * preYVelocity * preYVelocity;
			}
			else
			{
				yForces += 1 * obj.GetDragCoefficient() * preYVelocity * preYVelocity;
			}
		}
		
		for (std::vector<Point2D>::iterator fo = forces.begin(); fo != forces.end(); ++fo)
		{
			xForces += fo->getXPosition();
			yForces += fo->getYPosition();
		}

		obj.SetXAcceleration(xForces / obj.GetMass());
		obj.SetYAcceleration(yForces / obj.GetMass());

		obj.posAndVec.setXVector(preXVelocity + obj.GetXAcceleration() * dT);
		obj.posAndVec.setYVector(preYVelocity + obj.GetYAcceleration() * dT);

		obj.posAndVec.setXPosition(obj.posAndVec.getXPosition() + ((preXVelocity + obj.posAndVec.getXVector()) / 2) * dT);
		obj.posAndVec.setYPosition(obj.posAndVec.getYPosition() + ((preYVelocity + obj.posAndVec.getYVector()) / 2) * dT);

		if (obj.posAndVec.getXVector() < .01f && obj.posAndVec.getXVector() > -.01f)
		{
			obj.posAndVec.setXVector(0);
		}
		if (obj.posAndVec.getYVector() < .01f && obj.posAndVec.getYVector() > -.01f)
		{
			obj.posAndVec.setYVector(0);
		}

	}
	void Shutdown()
	{
		AllPhysicsObjects.clear();
		delete& AllPhysicsObjects;
	}
}