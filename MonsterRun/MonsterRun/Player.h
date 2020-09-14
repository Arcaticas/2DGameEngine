#pragma once
#ifndef PLAYER
#define PLAYER
#include "Actor.h"

class Player : public Actor {

public:
	const char* name;
	int xPosition;
	int yPosition;

	Player();
	Player(char*);
	void Move(char c);


	const char* getName() { return name; }
	int getXPosition() { return xPosition; }
	int getYPosition() { return yPosition; }
};

#endif // !PLAYER
