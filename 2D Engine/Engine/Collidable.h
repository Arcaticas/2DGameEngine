#pragma once
#include "Point2D.h"
#include "GameObjectObserver.h"
#include "2DPhysicsObj.h"

namespace Collision
{
	class Collidable
	{



	private:
		GameObjectObserver<Physics::TwoDPhysicsObj> m_owner;
		Point2D center;
		Point2D extent;
	};

}