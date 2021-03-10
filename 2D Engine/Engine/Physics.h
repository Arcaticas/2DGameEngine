#pragma once
#include <vector>
#include "2DPhysicsObj.h"


namespace Physics
{
	float GetFrameTime();
	void Update(TwoDPhysicsObj& obj, std::vector<Point2D>& forces, float dT);
}