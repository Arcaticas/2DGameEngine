#pragma once
#include <assert.h>
#include "Counters.h"


template <typename T>
class GameObjectOwner
{
	template <typename T>
	friend class GameObjectObserver;
public:
	template <typename T>
	GameObjectOwner() :
		m_ptr(nullptr),
		m_count(new Counters(0, 0))
	{	
	}

	template <typename T>
	GameObjectOwner(T* i_ptr) :
		m_count(new Counters(1, 0))
	{
		m_ptr = i_ptr;
	}
	template <typename T>
	GameObjectOwner(const GameObjectOwner<T>& i_copy)
	{
		m_ptr = i_copy.m_ptr;
		m_count = i_copy.m_count;
		(*m_count).m_Owners++;
	}

	template <typename T>
	GameObjectOwner(const GameObjectObserver<T>& i_copy)
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