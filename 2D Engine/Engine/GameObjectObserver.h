#pragma once
#include "GameObjectOwner.h"

template <typename T>
class GameObjectObserver
{
	template <typename T>
	friend class GameObjectOwner;
public:


	template <typename T>
	GameObjectObserver(const GameObjectOwner<T>& i_owner)
	{
		m_ptr = i_owner.m_ptr;
		m_count = i_owner.m_count;
		(*m_count).m_Observers++;
	}

	~GameObjectObserver()
	{
		(*m_count).m_Observers--;
		if ((*m_count).m_Observers == 0 && (*m_count).m_Owners == 0)
		{
			delete m_count;
		}
	}

	template <typename T>
	GameObjectOwner<T> CreateOwner()
	{
		if ((*m_count).m_Owners > 0)
		{
			return GameObjectOwner<T>(*this);
		}
		return GameObjectOwner<T>();
	}

private:
	T* m_ptr;
	Counters* m_count;

};