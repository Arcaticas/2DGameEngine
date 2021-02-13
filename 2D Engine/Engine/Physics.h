#pragma once
#include <vector>
#include "2DPhysicsObj.h"


struct Vector2
{
public:
	float x;
	float y;

	Vector2(float i_x, float i_y)
	{
		x = i_x;
		y = i_y;
	}
};

struct Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3(float i_x, float i_y, float i_z)
	{
		x = i_x;
		y = i_y;
		z = i_z;
	}
};

namespace Physics
{
	float GetFrameTime();
	void Update(TwoDPhysicsObj& obj, float dT, std::vector<Vector2>& forces);
}