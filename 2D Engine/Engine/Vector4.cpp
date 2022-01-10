#include "Vector4.h"


namespace Matrix
{
	Vector4::Vector4() :
		m_x(0),
		m_y(0),
		m_z(0),
		m_w(0)
	{
	}

	Vector4::Vector4(float i_x, float i_y, float i_z, float i_w) :
		m_x(i_x),
		m_y(i_y),
		m_z(i_z),
		m_w(i_w)
	{
	}

}

