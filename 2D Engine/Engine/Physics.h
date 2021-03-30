#pragma once
#include <vector>
#include "2DPhysicsObj.h"
#include "GameObjectOwner.h"


namespace Physics
{
	static std::vector<TwoDPhysicsObj> AllPhysicsObjects;

	float GetFrameTime();
	GameObjectOwner<TwoDPhysicsObj> CreatePhysicsObject(float i_xPos, float i_yPos);
	void Update(TwoDPhysicsObj& obj, std::vector<Point2D>& forces, float dT);
}