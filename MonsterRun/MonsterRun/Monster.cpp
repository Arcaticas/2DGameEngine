#include <iostream>
#include "Monster.h"

using namespace std;

Monster::Monster()
{

}

Monster::Monster(char* n, GameObject* player, int x, int y)
{
	Attach(&Name(n));
	Attach(&AiController(player));
	position = Point2D(x, y);
}

void Monster::UpdateObject()
{

	const size_t count = components.size();
	for (size_t i = 0; i < count; i++)
	{
		components[i]->Update(*this);
	}

}