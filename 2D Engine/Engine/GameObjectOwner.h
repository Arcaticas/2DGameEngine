#pragma once
#include <assert.h>
#include "GameObject.h"
#include "Counters.h"

class GameObjectObserver;

class GameObjectOwner
{
	friend class GameObjectObserver;
public:
	GameObjectOwner(GameObject* i_ptr);
	GameObjectOwner(const GameObjectOwner& i_copy);
	GameObjectOwner(const GameObjectObserver& i_copy);

	~GameObjectOwner();

	GameObject* operator->();
	GameObject& operator*();

private:
	GameObject* m_ptr;
	Counters* count;
};

