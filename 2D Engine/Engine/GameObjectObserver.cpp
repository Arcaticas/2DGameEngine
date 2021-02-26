#include "GameObjectObserver.h"


GameObjectObserver::GameObjectObserver(const GameObjectOwner& i_owner)
{
	m_ptr = i_owner.m_ptr;
	count = i_owner.count;
	(*count).m_Observers++;
}

GameObjectObserver::~GameObjectObserver()
{
	(*count).m_Observers--;
	if ((*count).m_Observers == 0 && (*count).m_Owners == 0)
	{
		delete count;
	}
}

GameObjectOwner GameObjectObserver::CreateOwner()
{
	if ((*count).m_Owners > 0)
	{
		return GameObjectOwner(*this);
	}
	return nullptr;
}

