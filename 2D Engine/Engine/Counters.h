#pragma once

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