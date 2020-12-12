#include <iostream>
#include <conio.h>
#include <stdio.h>
#include "Monster.h"
#include "Actor.h"


int main()
{

	void Point2DUnitTest();
	std::cout << "2DUnitTest Passed\n";





	bool gameRunning = true;
	Actor you;
	const size_t lenInput = 128;
	char Input[lenInput];

	std::cout << "Welcome to monster run!\n";
	std::cout << "Enter your player name:\n";
	
	
	gets_s(Input, lenInput);
	you = Actor(Input,0,0);

	int numbMonsters = 0;
	std::cout << "How many monsters would you like to run from?\n";
	while (numbMonsters <= 0) {
		gets_s(Input, lenInput);
		numbMonsters = atoi(Input);
		if (numbMonsters <= 0) {
			std::cout << "Bad input. Enter a postive int.\n";
		}
	}
	

	Monster* pMonsters;

	pMonsters = new (std::nothrow) Monster[numbMonsters];
	if (pMonsters == nullptr) 
	{
		//delete[] pMonsters;
	}
	else 
	{
		std::cout << "Awesome!\n";
	}



	for(int i = 0; i < numbMonsters; i++) 
	{
		
		std::cout << "What would you like to name monster " << i+1 << ":\n";
		if (pMonsters != 0) {
			pMonsters[i] = Monster(gets_s(Input, lenInput));
		}
			
	}

	
	char input;
	int turnCount = 0;

	while (gameRunning) {
		turnCount++;

		if (turnCount % 5 == 0) {
			numbMonsters--;
			Monster* temp;
			temp = new (std::nothrow) Monster[numbMonsters];
			for (int i = 0; i < numbMonsters; i++) {
				temp[i] = pMonsters[i + 1];
			}
			delete[] pMonsters;
			pMonsters = new (std::nothrow) Monster[numbMonsters];
			for (int i = 0; i < numbMonsters; i++) {
				pMonsters[i] = temp[i];
			}
			//delete[] temp;
		}

		if (turnCount % 3 == 0) {
			numbMonsters++;
			Monster* temp;

			temp = new (std::nothrow) Monster[numbMonsters];
			if (temp != 0) {
				for (int i = 0; i < numbMonsters; i++) {
					if (pMonsters != 0) {
						temp[i] = pMonsters[i];

					}
				}

				delete[] pMonsters;
				std::cout << "Enter the new monsters name: \n";
				temp[numbMonsters - 1] = Monster(gets_s(Input, lenInput));

				pMonsters = new (std::nothrow) Monster[numbMonsters];

				for (int i = 0; i < numbMonsters; i++) {
					if (pMonsters != 0) 
					{
						pMonsters[i] = temp[i];
					}
				}
				delete[] temp;
			}
			
		}
		if (pMonsters != 0) {
			for (int i = 0; i < numbMonsters; i++)
			{
				std::cout << pMonsters[i].getName() << " is at (" << pMonsters[i].getXPosition() << ',' << pMonsters[i].getYPosition() << ").\n";
				if (pMonsters[i].getXPosition() == you.getXPosition() && pMonsters[i].getYPosition() == you.getYPosition())
				{
					std::cout << "A monster got you! Hit any key to quit.";
					input = _getch();
					break;
				}
			}
			std::cout << "You are at (" << you.getXPosition() << ',' << you.getYPosition() << "). Move now with WASD. Quit with ESC.\n";

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
				//pMonsters[i].Move(you);
			}
		}
		
	}


	delete[] pMonsters;
	return 0;
}