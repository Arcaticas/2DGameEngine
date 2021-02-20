#pragma once
#include "GameObject.h"


struct Counters
{
	unsigned long m_Owners;
	unsigned long m_Observers;

	Counters(unsigned long i_Owners, unsigned long i_Observers) :
		m_Owners(i_Owners),
		m_Observers(i_Observers)
	{
	}
};


class GameObjectOwner
{
public:
	GameObjectOwner(GameObject* i_ptr);
	GameObjectOwner(GameObjectOwner& i_copy);

	~GameObjectOwner();

	GameObject* operator->();

private:
	GameObject* m_ptr;
	Counters* count;
};

