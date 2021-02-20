#include "GameObjectObserver.h"


GameObjectObserver::GameObjectObserver(const GameObjectOwner& i_owner)
{
	m_ptr = i_owner.m_ptr;
}

GameObjectObserver::~GameObjectObserver()
{

}

GameObject* GameObjectObserver::operator->()
{
	return nullptr;
}
