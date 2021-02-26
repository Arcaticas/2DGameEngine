#pragma once
#include "GameObjectOwner.h"


class GameObjectObserver
{
	friend class GameObjectOwner;
public:
	GameObjectObserver(const GameObjectOwner& i_owner);

	~GameObjectObserver();

	GameObjectOwner CreateOwner();

private:
	GameObject* m_ptr;
	Counters* count;

};