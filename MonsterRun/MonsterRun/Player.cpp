#include <iostream>
#include <conio.h>
#include "Player.h"
using namespace std;


Player::Player() {
	name = new char[2]{ 't','j' };

	xPosition = 0;
	yPosition = 0;
}

Player::Player(char* n) {

	name = n;
		
	xPosition = 0;
	yPosition = 0;

}

/*void Player::Move(char c) {
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
	
}*/