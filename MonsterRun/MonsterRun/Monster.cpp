#include <iostream>
#include "Monster.h"

using namespace std;

Monster::Monster()
{
	name = nullptr;
}

Monster::Monster(char* n, GameObject* player, int x, int y)
{
	Attach(new Name(n));
	name = n;
	Attach(new AiController(player));
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