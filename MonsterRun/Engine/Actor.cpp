#include <conio.h>
#include <iostream>

#include "Actor.h"

Actor::Actor()
{
	
	Object2D();

}


Actor::Actor(char* n, int xPos, int yPos)
{

	Object2D(n, xPos, yPos);

}

Actor::Actor(char* n, int xPos, int yPos, int xVec, int yVec)
{
	
	Object2D(n, xPos, yPos, xVec, yVec);

}

void Actor::Move(char c)
{
	if (c != 'w' && c != 'a' && c != 's' && c != 'd')
	{
		std::cout << "Use WASD to move.\n";
		Move(_getch());
	}

	if (c == 'w')
	{
		setXPosition(getYPosition() + 1);
	}
	if (c == 'a')
	{
		setXPosition(getXPosition() - 1);
	}
	if (c == 's')
	{
		setXPosition(getYPosition() - 1);
	}
	if (c == 'd')
	{
		setXPosition(getXPosition() + 1);
	}
}