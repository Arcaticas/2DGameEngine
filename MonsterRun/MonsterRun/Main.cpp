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


	cout << "Welcome to monster run!\n";
	cout << "Enter your player name:\n";
	char playerName[20];
	cin >> playerName;

	you = Player(playerName);




	/*char *namePointer;
	namePointer = playerName;

	while (*namePointer!= '\0') {
		cout << *namePointer;
		namePointer++;
	}*/

	int numbMonsters;
	cout << "How many monsters would you like to run from?\n";
	cin >> numbMonsters;

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
		char monsterName[20];
		cout << "What would you like to name monster " << i+1 << "\n";
		cin >> monsterName;
		pMonsters[i] = Monster(monsterName);
	}

	
	char input;
	while (gameRunning) {
		for (int i = 0; i < numbMonsters; i++) 
		{
			cout << pMonsters[i].getName() << " is at (" << pMonsters[i].getXPosition() << ',' << pMonsters[i].getYPosition() << ").\n";
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