#pragma once
#include <vector>
#include "2DPhysicsObj.h"
#include "GameObjectOwner.h"


namespace Physics
{
	static std::vector<TwoDPhysicsObj*>& AllPhysicsObjects = *(new std::vector<TwoDPhysicsObj*>());

	float GetFrameTime();
	GameObjectOwner<TwoDPhysicsObj> CreatePhysicsObject(const float i_xPos,const float i_yPos);
	void Update(TwoDPhysicsObj& obj, std::vector<Point2D>& forces, float dT);

	void Shutdown();
}