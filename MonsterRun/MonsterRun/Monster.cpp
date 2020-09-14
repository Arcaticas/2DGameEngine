#include <iostream>
#include "Monster.h"
#include "Player.h"

using namespace std;


Monster::Monster() {
	name = new char[2]{ 't','j' };

	xPosition = 10;
	yPosition = -10;
}

Monster::Monster(char* n) {

	name = n;
	xPosition = (int)n[0] - 60;

	if ((int)n[1] == 0 || (int)n[1] == -52) {
			yPosition = xPosition;
	}
	else
	{
		yPosition = (int)n[1] - 60;
	}
}

void Monster::Move(Actor p) {
	if (p.getXPosition() > xPosition) 
	{
		xPosition++;
		if (p.getYPosition() > yPosition)
		{
			yPosition++;
		}
		else if (p.getYPosition() < yPosition)
		{
			yPosition--;
		}
		else
		{
			xPosition++;
		}
		
	}
	else if (p.getXPosition() < xPosition)
	{
		xPosition--;
		if (p.getYPosition() > yPosition)
		{
			yPosition++;
		}
		else if (p.getYPosition() < yPosition)
		{
			yPosition--;
		}
		else
		{
			xPosition--;
		}

	}
	else
	{
		yPosition += 2;
	}
	
}
