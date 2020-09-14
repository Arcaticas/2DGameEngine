#pragma once
#ifndef ACTOR
#define ACTOR
#include "Object2D.h"

class Actor : public Object2D
{
public:
	Actor();
	Actor(char* n, int xPos, int yPos);
	Actor(char* n, int xPos, int yPos, int xVec, int yVec);

	void Move(char);
};
#endif // !ACTOR
