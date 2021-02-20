#pragma once
#include "GameObjectOwner.h"

class GameObjectObserver
{
public:
	GameObjectObserver(const GameObjectOwner& i_owner);

	~GameObjectObserver();

	GameObjectOwner CreateOwner();
	GameObject* operator->();

private:
	GameObject* m_ptr;
	Counters* count;
};