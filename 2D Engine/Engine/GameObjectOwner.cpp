#include "GameObject.h"
#include "GameObjectOwner.h"



GameObjectOwner::GameObjectOwner(GameObject* i_ptr) :
	m_ptr(i_ptr),
	count(new Counters(1,0))
{
}

GameObjectOwner::GameObjectOwner(GameObjectOwner& i_copy)
{
	m_ptr = i_copy.m_ptr;
	count = i_copy.count;
	(*count).m_Owners++;
}

GameObjectOwner::~GameObjectOwner()
{
	if (--((*count).m_Owners) == 0)
	{
		delete m_ptr;
		if ((*count).m_Observers == 0)
		{
			delete count;
		}
	}
}

GameObject* GameObjectOwner::operator->()
{
	return m_ptr;
}

