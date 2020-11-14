#include <iostream>
#include <conio.h>
#include <stdio.h>
#include "Monster.h"
#include "Player.h"

int main()
{
	bool gameRunning = true;
	Player you;
	const size_t lenInput = 128;
	char Input[lenInput];

	std::cout << "Welcome to monster run!\n";
	std::cout << "Enter your player name:\n";
	
	
	gets_s(Input, lenInput);
	you = Player(Input, 10, 10);
	size_t numbMonsters = 0;
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
			pMonsters[i].Attach(&Name(gets_s(Input, lenInput)));
		}
			
	}

	
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
				temp[numbMonsters - 1].Attach(&Name(gets_s(Input, lenInput)));
				temp[numbMonsters - 1].Attach(&AiController(reinterpret_cast<GameObject>(you)));

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
				std::cout << pMonsters[i].getName() << " is at (" << pMonsters[i].position.getXPosition() << ',' << pMonsters[i].position.getYPosition() << ").\n";
				if (pMonsters[i].position.getXPosition() == you.position.getXPosition() && pMonsters[i].position.getYPosition() == you.position.getYPosition())
				{
					std::cout << "A monster got you! Hit any key to quit.";
					input = _getch();
					break;
				}
			}
			std::cout << "You are at (" << you.position.getXPosition() << ',' << you.position.getYPosition() << "). \n";

			input = _getch();

			if (input == 27) {
				break;
			}
			else
			{
				you.UpdateObject();
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