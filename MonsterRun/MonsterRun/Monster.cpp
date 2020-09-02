#include <iostream>
#include "Monster.h"
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
	xPosition = (int)n[0];

	if ((int)n[1] == 0 || (int)n[1] == -52) {
			yPosition = (int)n[0];
	}
	else
	{
		yPosition = (int)n[1];
	}
}
