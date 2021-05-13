#pragma once
#include <vector>
#include "Collidable.h"

namespace Collision
{
	extern std::vector<Collidable>& AllCollidables;

	bool IsCollidingStatic(Collidable& i_a, Collidable& i_b);
	bool IsCollidingSweep(Collidable& i_a, Collidable& i_b, float frameTime);

	void Shutdown();

}