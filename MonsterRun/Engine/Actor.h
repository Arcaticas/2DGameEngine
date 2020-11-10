#pragma once
#ifndef ACTOR
#define ACTOR
#include "GameObject.h"
#include "NameComp.h"

class Actor : public GameObject
{
public:
	Actor();
	Actor(char* n, int x, int y);
};
#endif // !ACTOR
