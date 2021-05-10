#pragma once

namespace Matrix
{
	inline bool Vector4::operator==(const Vector4& i_vector)
	{
		if (this->GetX() == i_vector.GetX() && this->GetY() == i_vector.GetY() && this->GetZ() == i_vector.GetZ() && this->GetW() == i_vector.GetW())
			return true;
		else
			return false;
	}

	inline Vector4 Vector4::operator+=(const Vector4& i_vector)
	{
		return Vector4(m_x + i_vector.GetX(), m_y + i_vector.GetY(), m_z + i_vector.GetZ(), m_w + i_vector.GetW());
	}

	inline Vector4 Vector4::operator-=(const Vector4& i_vector)
	{
		return Vector4(m_x - i_vector.GetX(), m_y - i_vector.GetY(), m_z - i_vector.GetZ(), m_w - i_vector.GetW());
	}

	inline Vector4 Vector4::operator*=(const float i_scalar)
	{
		return Vector4(m_x * i_scalar, m_y * i_scalar, m_z * i_scalar, m_w * i_scalar);
	}

	inline Vector4 Vector4::operator/=(const float i_scalar)
	{
		return Vector4(m_x / i_scalar, m_y / i_scalar, m_z / i_scalar, m_w / i_scalar);
	}

	inline Vector4 Vector4::operator-()
	{
		return Vector4(-m_x, -m_y, -m_z, -m_w);
	}

	inline bool operator==(const Vector4& i_a, const Vector4& i_b)
	{
		return i_a.GetX() == i_b.GetX() && i_a.GetY() == i_b.GetY() && i_a.GetZ() == i_b.GetZ() && i_a.GetW() == i_b.GetW();
	}

	inline bool operator!=(const Vector4& i_a, const Vector4& i_b)
	{
		return !(i_a == i_b);
	}

	inline Vector4 operator+(const Vector4& i_a, const Vector4& i_b)
	{
		return Vector4(i_a.GetX() + i_b.GetX(), i_a.GetY() + i_b.GetY(), i_a.GetZ() + i_b.GetZ(), i_a.GetW() + i_b.GetW());
	}

	inline Vector4 operator-(const Vector4& i_a, const Vector4& i_b)
	{
		return Vector4(i_a.GetX() - i_b.GetX(), i_a.GetY() - i_b.GetY(), i_a.GetZ() - i_b.GetZ(), i_a.GetW() - i_b.GetW());
	}

	inline Vector4 operator*(const Vector4& i_vector, const float i_scalar)
	{
		return Vector4(i_vector.GetX() * i_scalar, i_vector.GetY() * i_scalar, i_vector.GetZ() * i_scalar, i_vector.GetW() * i_scalar);
	}

	inline Vector4 operator/(const Vector4& i_vector, const float i_scalar)
	{
		return Vector4(i_vector.GetX() / i_scalar, i_vector.GetY() / i_scalar, i_vector.GetZ() / i_scalar, i_vector.GetW() / i_scalar);
	}
}