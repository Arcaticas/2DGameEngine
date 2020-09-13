#pragma once
#ifndef MONSTER
#define MONSTER
#include "Player.h"

class Monster {

public:
	char name[20];
	int xPosition;
	int yPosition;

	Monster();
	Monster(char* n);
	void Move(Player p);

	char* getName() { return name; }
	int getXPosition() { return xPosition; }
	int getYPosition() { return yPosition; }
};


#endif




