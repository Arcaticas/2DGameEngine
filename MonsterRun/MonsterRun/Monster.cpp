#include <iostream>
#include "Monster.h"
#include "Player.h"

using namespace std;


Monster::Monster() {
	name[1] = 't';
	name[2] = 'j';

	xPosition = 10;
	yPosition = -10;
}

Monster::Monster(char n[]) {

	for (int i = 0; i < sizeof(n); i++)
	{
		name[i] = n[i];

	}
	xPosition = (int)n[0] - 60;

	if ((int)n[1] == 0 || (int)n[1] == -52) {
			yPosition = xPosition;
	}
	else
	{
		yPosition = (int)n[1] - 60;
	}
}

void Monster::Move(Player p) {
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
