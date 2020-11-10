#pragma once
#ifndef PLAYER
#define PLAYER
#include "GameObject.h"
#include "NameComp.h"
#include "PlayerControllerComp.h"

class Player : public GameObject {

public:

	Player();
	Player(char* n, int x, int y);

	void UpdateObject();
};

#endif // !PLAYER
