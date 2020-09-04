#include <iostream>
#include <conio.h>
#include <stdio.h>
#include "Monster.h"
#include "Player.h"

using namespace std;


int main()
{
	bool gameRunning = true;
	Player you;
	const size_t lenInput = 128;
	char Input[lenInput];

	cout << "Welcome to monster run!\n";
	cout << "Enter your player name:\n";
	

	gets_s(Input, lenInput);
	you = Player(Input);

	int numbMonsters = 0;
	cout << "How many monsters would you like to run from?\n";
	while (numbMonsters == 0) {
		gets_s(Input, lenInput);
		numbMonsters = atoi(Input);
		if (numbMonsters == 0) {
			cout << "Bad input. Enter an int.\n";
		}
	}
	

	Monster* pMonsters;

	pMonsters = new (nothrow) Monster[numbMonsters];
	if (pMonsters == nullptr) 
	{
		cout << "Oops";
	}
	else 
	{
		cout << "Awesome!\n";
	}



	for(int i = 0; i < numbMonsters; i++) 
	{
		
		cout << "What would you like to name monster " << i+1 << "\n";
		pMonsters[i] = Monster(gets_s(Input, lenInput));
	}

	
	char input;
	int turnCount = 0;

	while (gameRunning) {
		turnCount++;

		if (turnCount % 5 == 0) {
			numbMonsters--;
			Monster* temp;
			temp = new (nothrow) Monster[numbMonsters];
			for (int i = 0; i < numbMonsters; i++) {
				temp[i] = pMonsters[i + 1];
			}
			delete[] pMonsters;
			pMonsters = new (nothrow) Monster[numbMonsters];
			for (int i = 0; i < numbMonsters; i++) {
				pMonsters[i] = temp[i];
			}
			//delete[] temp;
		}

		if (turnCount % 3 == 0) {
			numbMonsters++;
			Monster* temp;
			temp = new (nothrow) Monster[numbMonsters];
			for (int i = 0; i < numbMonsters; i++) {
				temp[i] = pMonsters[i];
			}

			delete[] pMonsters;
			cout << "Enter the new monsters name: \n";
			temp[numbMonsters - 1] = Monster(gets_s(Input, lenInput));

			pMonsters = new (nothrow) Monster[numbMonsters];

			for (int i = 0; i < numbMonsters; i++) {
				pMonsters[i] = temp[i];
			}
			delete[] temp;
		}

		for (int i = 0; i < numbMonsters; i++) 
		{
			cout << pMonsters[i].getName() << " is at (" << pMonsters[i].getXPosition() << ',' << pMonsters[i].getYPosition() << ").\n";
			if (pMonsters[i].getXPosition() == you.getXPosition() && pMonsters[i].getYPosition() == you.getYPosition()) 
			{
				cout << "A monster got you! Hit any key to quit.";
				input = _getch();
				break;
			}
		}
		cout << "You are at (" << you.getXPosition() << ',' << you.getYPosition() << "). Move now with WASD.\n";

		input = _getch();
		
		if (input == 27) {
			break;
		}
		else
		{
			you.Move(input);
		}
		
		for (int i = 0; i < numbMonsters; i++)
		{
			pMonsters[i].Move(you);
		}
	}


	delete[] pMonsters;
	return 0;
}