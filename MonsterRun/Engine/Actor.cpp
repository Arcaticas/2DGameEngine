#include <conio.h>
#include <iostream>

#include "Actor.h"

Actor::Actor()
{
	Attach(&Name());
}


Actor::Actor(char* n, int xPos, int yPos)
{
	Attach(new Name(n));
	position = Point2D(xPos, yPos);
}

