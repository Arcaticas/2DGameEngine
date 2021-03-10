#include "GameObjectObserver.h"


GameObjectObserver::GameObjectObserver(const GameObjectOwner& i_owner)
{
	m_ptr = i_owner.m_ptr;
	m_count = i_owner.m_count;
	(*m_count).m_Observers++;
}

GameObjectObserver::~GameObjectObserver()
{
	(*m_count).m_Observers--;
	if ((*m_count).m_Observers == 0 && (*m_count).m_Owners == 0)
	{
		delete m_count;
	}
}

GameObjectOwner GameObjectObserver::CreateOwner()
{
	if ((*m_count).m_Owners > 0)
	{
		return GameObjectOwner(*this);
	}
	return nullptr;
}

