#pragma once
#include "Matrix3x3.h"
#include "Vector4.h"


namespace Matrix
{
	class Matrix4x4
	{
	public:
		Matrix4x4();
		Matrix4x4(float i_r1c1, float i_r1c2, float i_r1c3, float i_r1c4,
				  float i_r2c1, float i_r2c2, float i_r2c3, float i_r2c4,
				  float i_r3c1, float i_r3c2, float i_r3c3, float i_r3c4,
				  float i_r4c1, float i_r4c2, float i_r4c3, float i_r4c4);

		Matrix4x4 operator+=(const Matrix4x4& i_matrix);
		Matrix4x4 operator-=(const Matrix4x4& i_matrix);
		Matrix4x4 operator*=(const float i_scalar);
		Vector4 operator*=(const Vector4&);
		Matrix4x4 operator/=(const float i_scalar);

		

		float GetValue(int i_row, int i_col);
		void SetValue(int i_row, int i_col, float i_value);

		float Get4x4Determinate();
		float Get4x4CofactorDeterminate(int i_dRow, int i_dCol);

		Matrix4x4 Tranpose();
		Matrix4x4 Invert();
	private:
		float r1c1, r1c2, r1c3, r1c4,
			  r2c1, r2c2, r2c3, r2c4,
			  r3c1, r3c2, r3c3, r3c4,
			  r4c1, r4c2, r4c3, r4c4;
	};
}