#pragma once


namespace Matrix
{
	class Vector4
	{
	public:
		Vector4();
		Vector4(float x, float y, float z, float w);

		inline bool operator==(const Vector4&);

		inline Vector4 operator+=(const Vector4&);
		inline Vector4 operator-=(const Vector4&);
		inline Vector4 operator*=(const float);
		inline Vector4 operator/=(const float);
		inline Vector4 operator-();

		void SetX(const float i_x) { m_x = i_x; }
		void SetY(const float i_y) { m_x = i_y; }
		void SetZ(const float i_z) { m_z = i_z; }
		void SetW(const float i_w) { m_w = i_w; }
		float GetX() const { return m_x; }
		float GetY() const { return m_y; }
		float GetZ() const { return m_z; }
		float GetW() const { return m_w; }


	private:
		float m_x, m_y, m_z, m_w;
	};

	inline bool operator==(const Vector4&, const Vector4&);
	inline bool operator!=(const Vector4&, const Vector4&);

	inline Vector4 operator+(const Vector4&, const Vector4&);
	inline Vector4 operator-(const Vector4&, const Vector4&);
	inline Vector4 operator*(const Vector4&, const float);
	inline Vector4 operator/(const Vector4&, const float);


}

#include "Vector4-inl.h"