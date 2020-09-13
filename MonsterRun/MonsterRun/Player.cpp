#include <iostream>
#include <conio.h>
#include "Player.h"
using namespace std;


Player::Player() {
	name[0] = 'j';
	name[1] = 't';

	xPosition = 0;
	yPosition = 0;
}

Player::Player(char n[]) {

	for (int i = 0; i < sizeof(n); i++)
	{
		name[i] = n[i];

	}
		
	xPosition = 0;
	yPosition = 0;

}

void Player::Move(char c) {
	cout << c;
	bool acting = true;
	while (acting) {
		if (c == 'w') {
			yPosition++;
			acting = false;
		}
		else if (c == 'd') {
			xPosition++;
			acting = false;
		}
		else if (c == 's') {
			yPosition--;
			acting = false;
		}
		else if (c == 'a') {
			xPosition--;
			acting = false;
		}
		else {
			cout << "Use WASD to move.\n";
			Move(_getch());
			break;
		}
	}
	
}