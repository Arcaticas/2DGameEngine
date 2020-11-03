#include "Vector2.h"

namespace Engine
{
	namespace Math
	{

		const Vector2 Vector2::Zero(0.0f, 0.0f);

		Vector2::Vector2(float i_x, float i_y) :
			m_x(i_x),
			m_y(i_y)
		{
		}

		Vector2::Vector2(const Vector2& i_other) :
			m_x(i_other.m_x),
			m_y(i_other.m_y)
		{
		}

		Vector2 Vector2::Normalized() const
		{
			float length = Length();

			if (length == 0.0f)
				return Zero;
			else
			{
				float inv_length = 1.0f / length;

				return *this * inv_length;
			}
		}

		Vector2 Normalized(const Vector2& i_vec)
		{
			float length = i_vec.Length();

			if (length == 0.0f)
				return Vector2::Zero;
			else
			{
				float inv_length = 1.0f / length;

				return i_vec * inv_length;
			}
		}

	} // namespace Math
} // namespace Engine