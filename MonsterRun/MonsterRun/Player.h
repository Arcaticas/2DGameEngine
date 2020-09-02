#pragma once
#ifndef PLAYER
#define PLAYER

class Player {

public:
	char name[20];
	int xPosition;
	int yPosition;

	Player();
	Player(char[]);
	void Move(char c);


	char* getName() { return name; }
	int getXPosition() { return xPosition; }
	int getYPosition() { return yPosition; }
};

#endif // !PLAYER
