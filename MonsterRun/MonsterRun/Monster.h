#pragma once
#ifndef MONSTER
#define MONSTER
#include "Actor.h"

class Monster {

public:
	const char* name;
	int xPosition;
	int yPosition;

	Monster();
	Monster(char* n);
	void Move(Actor p);

	const char* getName() { return name; }
	int getXPosition() { return xPosition; }
	int getYPosition() { return yPosition; }
};


#endif




