#include <iostream>
#include "Monster.h"

using namespace std;



int main()
{
	
	cout << "Welcome to monster run!\n";
	cout << "Enter your player name:\n";
	char playerName[20];
	cin >> playerName;

	




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
		cout << "Awesome!";
	}



	for(int i = 0; i < numbMonsters; i++) 
	{
		cout << "What would you like to name monster " << i+1 << "\n";
		
	}

	return 0;
}