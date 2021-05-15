#pragma once
#include <vector>
#include "Collidable.h"

namespace Collision
{
	extern std::vector<Collidable>& AllCollidables;

	Collidable GetCollidable(GameObjectOwner<Physics::TwoDPhysicsObj> i_ptr);

	bool IsCollidingStatic(Collidable& i_a, Collidable& i_b);
	bool IsCollidingSweep(Collidable& i_a, Collidable& i_b, float frameTime);

	void CreateCollidable(GameObjectOwner<Physics::TwoDPhysicsObj>& i_owner, float i_xExtent, float i_yExtent);

	void Shutdown();

}