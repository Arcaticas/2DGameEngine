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

	GameObjectObserver(const GameObjectObserver<T>& i_observer)
	{
		m_ptr = i_observer.m_ptr;
		m_count = i_observer.m_count;
		(*m_count).m_Observers++;
	}

	~GameObjectObserver()
	{
		assert((*m_count).m_Observers > 0);
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
		return nullptr;
	}

	void operator=(const GameObjectObserver<T>& i_other)
	{
		assert((*m_count).m_Observers > 0);
		(*m_count).m_Observers--;
		if ((*m_count).m_Observers == 0 && (*m_count).m_Owners == 0)
		{
			delete m_count;
		}

		m_ptr = i_other.m_ptr;
		m_count = i_other.m_count;
		(*m_count).m_Observers++;
	}

	bool operator==(const GameObjectObserver<T>& i_other)
	{
		return m_ptr == i_other.m_ptr;
	}

private:
	T* m_ptr;
	Counters* m_count;

};