#include "PlayerControllerComp.h"
#include <conio.h>
#include <iostream>

PlayerController::PlayerController()
{
	input = '\0';
}

void PlayerController::GetInput(char c)
{
	input = c;
}

void PlayerController::Move(Point2D pos)
{

		if (input == 'w')
		{
			pos.setYPosition(pos.getYPosition() + 1);
		}
		if (input == 'a')
		{
			pos.setXPosition(pos.getXPosition() - 1);
		}
		if (input == 's')
		{
			pos.setYPosition(pos.getYPosition() - 1);
		}
		if (input == 'd')
		{
			pos.setXPosition(pos.getXPosition() + 1);
		}
}

void PlayerController::PreUpdate(GameObject& obj)
{
	std::cout << "WASD To move the player.\n";
	char temp = _getch();
	while (temp != 'w' && temp != 'a' && temp != 's' && temp != 'd')
	{
		std::cout << "WASD To move the player.\n";
		char temp = _getch();
	}
	GetInput(temp);
}

void PlayerController::Update(GameObject& obj)
{
	Move(obj.position);
}