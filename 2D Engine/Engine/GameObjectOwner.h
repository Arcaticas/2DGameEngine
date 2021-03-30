#pragma once
#include <assert.h>
#include "Counters.h"


template <typename T>
class GameObjectOwner
{
	template <typename U>
	friend class GameObjectObserver;
public:
	GameObjectOwner(T* i_ptr) :
		m_count(new Counters(1, 0))
	{
		m_ptr = i_ptr;
	}

	GameObjectOwner(const GameObjectOwner<T>& i_copy)
	{
		m_ptr = i_copy.m_ptr;
		m_count = i_copy.m_count;
		(*m_count).m_Owners++;
	}

	template <typename U>
	GameObjectOwner(const GameObjectObserver<U>& i_copy)
	{
		m_ptr = i_copy.m_ptr;
		m_count = i_copy.m_count;
		(*m_count).m_Owners++;
	}

	~GameObjectOwner()
	{
		if (--((*m_count).m_Owners) == 0)
		{
			delete m_ptr;
			if ((*m_count).m_Observers == 0)
			{
				delete m_count;
			}
		}
	}

	T* operator->()
	{
		return m_ptr;
	}
	T& operator*()
	{
		assert(m_ptr);
		return *m_ptr;
	}

private:
	T* m_ptr;
	Counters* m_count;
};