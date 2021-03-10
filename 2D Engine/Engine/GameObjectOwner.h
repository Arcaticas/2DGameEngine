#pragma once
#include <assert.h>
#include "Counters.h"
#include "2DPhysicsObj.h"

class GameObjectObserver;

class GameObjectOwner
{
	friend class GameObjectObserver;
public:
	GameObjectOwner(Physics::TwoDPhysicsObj* i_ptr);
	GameObjectOwner(const GameObjectOwner& i_copy);
	GameObjectOwner(const GameObjectObserver& i_copy);

	~GameObjectOwner();

	Physics::TwoDPhysicsObj* operator->();
	Physics::TwoDPhysicsObj& operator*();

private:
	Physics::TwoDPhysicsObj* m_ptr;
	Counters* m_count;
};

