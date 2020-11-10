#pragma once
#ifndef MONSTER
#define MONSTER
#include "GameObject.h"
#include "NameComp.h"
#include "AiControllerComp.h"

class Monster : public GameObject{

public:
	Monster(char* n, GameObject* target, int x, int y);

	void UpdateObject();
};


#endif




