#include "Player.h"


Player::Player() {
	Attach(&Name());
	Attach(&PlayerController());
	position = Point2D();
}

Player::Player(char* n, int x, int y) {

	Attach(&Name(n));
	Attach(&PlayerController());
	position = Point2D(x, y);

}

void Player::UpdateObject() 
{
	const size_t count = components.size();
	for (size_t i = 0; i < count; i++)
	{
		components[i]->PreUpdate(*this);
	}

	for (size_t i = 0; i < count; i++)
	{
			components[i]->Update(*this);
	}
}
