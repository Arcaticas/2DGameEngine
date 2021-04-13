#pragma once
#include <vector>
#include "Collidable.h"

namespace Collision
{
	static std::vector<Collidable> AllCollidables;

	bool IsColliding(Collidable i_a, Collidable i_b);

}