#include "Matrix4x4.h"


namespace Matrix
{
	Matrix4x4::Matrix4x4() :
		r1c1(0), r1c2(0), r1c3(0), r1c4(0),
		r2c1(0), r2c2(0), r2c3(0), r2c4(0),
		r3c1(0), r3c2(0), r3c3(0), r3c4(0),
		r4c1(0), r4c2(0), r4c3(0), r4c4(0)
	{

	}
	Matrix4x4::Matrix4x4(float i_r1c1, float i_r1c2, float i_r1c3, float i_r1c4, float i_r2c1, float i_r2c2, float i_r2c3, float i_r2c4, float i_r3c1, float i_r3c2, float i_r3c3, float i_r3c4, float i_r4c1, float i_r4c2, float i_r4c3, float i_r4c4) :
		r1c1(i_r1c1), r1c2(i_r1c2), r1c3(i_r1c3), r1c4(i_r1c4),
		r2c1(i_r2c1), r2c2(i_r2c2), r2c3(i_r2c3), r2c4(i_r2c4),
		r3c1(i_r3c1), r3c2(i_r3c2), r3c3(i_r3c3), r3c4(i_r3c4),
		r4c1(i_r4c1), r4c2(i_r4c2), r4c3(i_r4c3), r4c4(i_r4c4)
	{
	}

	Matrix4x4 Matrix4x4::operator+=(const Matrix4x4& i_matrix)
	{
		return Matrix4x4(
			this->GetValue(0, 0) + i_matrix.r1c1, this->GetValue(0, 1) + i_matrix.r1c2, this->GetValue(0, 2) + i_matrix.r1c3, this->GetValue(0, 3) + i_matrix.r1c4,
			this->GetValue(1, 0) + i_matrix.r2c1, this->GetValue(1, 1) + i_matrix.r2c2, this->GetValue(1, 2) + i_matrix.r2c3, this->GetValue(1, 3) + i_matrix.r2c4,
			this->GetValue(2, 0) + i_matrix.r3c1, this->GetValue(2, 1) + i_matrix.r3c2, this->GetValue(2, 2) + i_matrix.r3c3, this->GetValue(2, 3) + i_matrix.r3c4,
			this->GetValue(3, 0) + i_matrix.r4c1, this->GetValue(3, 1) + i_matrix.r4c2, this->GetValue(3, 2) + i_matrix.r4c3, this->GetValue(3, 3) + i_matrix.r4c4
		);
	}

	Matrix4x4 Matrix4x4::operator-=(const Matrix4x4& i_matrix)
	{
		return Matrix4x4(
			this->GetValue(0, 0) - i_matrix.r1c1, this->GetValue(0, 1) - i_matrix.r1c2, this->GetValue(0, 2) - i_matrix.r1c3, this->GetValue(0, 3) - i_matrix.r1c4,
			this->GetValue(1, 0) - i_matrix.r2c1, this->GetValue(1, 1) - i_matrix.r2c2, this->GetValue(1, 2) - i_matrix.r2c3, this->GetValue(1, 3) - i_matrix.r2c4,
			this->GetValue(2, 0) - i_matrix.r3c1, this->GetValue(2, 1) - i_matrix.r3c2, this->GetValue(2, 2) - i_matrix.r3c3, this->GetValue(2, 3) - i_matrix.r3c4,
			this->GetValue(3, 0) - i_matrix.r4c1, this->GetValue(3, 1) - i_matrix.r4c2, this->GetValue(3, 2) - i_matrix.r4c3, this->GetValue(3, 3) - i_matrix.r4c4
		);
	}

	Matrix4x4 Matrix4x4::operator*=(const float i_scalar)
	{
		return Matrix4x4(
			this->GetValue(0, 0) * i_scalar, this->GetValue(0, 1) * i_scalar, this->GetValue(0, 2) * i_scalar, this->GetValue(0, 3) * i_scalar,
			this->GetValue(1, 0) * i_scalar, this->GetValue(1, 1) * i_scalar, this->GetValue(1, 2) * i_scalar, this->GetValue(1, 3) * i_scalar,
			this->GetValue(2, 0) * i_scalar, this->GetValue(2, 1) * i_scalar, this->GetValue(2, 2) * i_scalar, this->GetValue(2, 3) * i_scalar,
			this->GetValue(3, 0) * i_scalar, this->GetValue(3, 1) * i_scalar, this->GetValue(3, 2) * i_scalar, this->GetValue(3, 3) * i_scalar
		);
	}

	Vector4 Matrix4x4::operator*=(const Vector4& i_v4)
	{
		return Vector4(i_v4.GetX() * this->GetValue(0, 0) + i_v4.GetX() * this->GetValue(0, 1) + i_v4.GetX() * this->GetValue(0, 2) + i_v4.GetX() * this->GetValue(0, 3),
			i_v4.GetY() * this->GetValue(1, 0) + i_v4.GetY() * this->GetValue(1, 1) + i_v4.GetY() * this->GetValue(1, 2) + i_v4.GetY() * this->GetValue(1, 3),
			i_v4.GetZ() * this->GetValue(2, 0) + i_v4.GetZ() * this->GetValue(2, 1) + i_v4.GetZ() * this->GetValue(2, 2) + i_v4.GetZ() * this->GetValue(2, 3),
			i_v4.GetW() * this->GetValue(3, 0) + i_v4.GetW() * this->GetValue(3, 1) + i_v4.GetW() * this->GetValue(3, 2) + i_v4.GetW() * this->GetValue(3, 3)
		);
	}

	Matrix4x4 Matrix4x4::operator/=(const float i_scalar)
	{
		return Matrix4x4(
			this->GetValue(0, 0) / i_scalar, this->GetValue(0, 1) / i_scalar, this->GetValue(0, 2) / i_scalar, this->GetValue(0, 3) / i_scalar,
			this->GetValue(1, 0) / i_scalar, this->GetValue(1, 1) / i_scalar, this->GetValue(1, 2) / i_scalar, this->GetValue(1, 3) / i_scalar,
			this->GetValue(2, 0) / i_scalar, this->GetValue(2, 1) / i_scalar, this->GetValue(2, 2) / i_scalar, this->GetValue(2, 3) / i_scalar,
			this->GetValue(3, 0) / i_scalar, this->GetValue(3, 1) / i_scalar, this->GetValue(3, 2) / i_scalar, this->GetValue(3, 3) / i_scalar
		);
	}

	float Matrix4x4::GetValue(int i_row, int i_col)
	{
		if ((i_col > 3 || i_col < 0) || (i_row > 3 || i_row < 0))
			return 0.0f;

		if (i_row == 0 && i_col == 0)
			return r1c1;
		if (i_row == 1 && i_col == 0)
			return r2c1;
		if (i_row == 2 && i_col == 0)
			return r3c1;
		if (i_row == 3 && i_col == 0)
			return r4c1;

		if (i_row == 0 && i_col == 1)
			return r1c2;
		if (i_row == 1 && i_col == 1)
			return r2c2;
		if (i_row == 2 && i_col == 1)
			return r3c2;
		if (i_row == 3 && i_col == 1)
			return r4c2;

		if (i_row == 0 && i_col == 2)
			return r1c3;
		if (i_row == 1 && i_col == 2)
			return r2c3;
		if (i_row == 2 && i_col == 2)
			return r3c3;
		if (i_row == 3 && i_col == 2)
			return r4c3;

		if (i_row == 0 && i_col == 3)
			return r1c4;
		if (i_row == 1 && i_col == 3)
			return r2c4;
		if (i_row == 2 && i_col == 3)
			return r3c4;
		if (i_row == 3 && i_col == 3)
			return r4c4;
		return 0;
	}

	void Matrix4x4::SetValue(int i_row, int i_col, float i_value)
	{
		if ((i_col > 3 || i_col < 0) || (i_row > 3 || i_row < 0))
			return;

		if (i_row == 0 && i_col == 0)
			r1c1 = i_value;
		if (i_row == 1 && i_col == 0)
			r2c1 = i_value;
		if (i_row == 2 && i_col == 0)
			r3c1 = i_value;
		if (i_row == 3 && i_col == 0)
			r4c1 = i_value;

		if (i_row == 0 && i_col == 1)
			r1c2 = i_value;
		if (i_row == 1 && i_col == 1)
			r2c2 = i_value;
		if (i_row == 2 && i_col == 1)
			r3c2 = i_value;
		if (i_row == 3 && i_col == 1)
			r4c2 = i_value;

		if (i_row == 0 && i_col == 2)
			r1c3 = i_value;
		if (i_row == 1 && i_col == 2)
			r2c3 = i_value;
		if (i_row == 2 && i_col == 2)
			r3c3 = i_value;
		if (i_row == 3 && i_col == 2)
			r4c3 = i_value;

		if (i_row == 0 && i_col == 3)
			r1c4 = i_value;
		if (i_row == 1 && i_col == 3)
			r2c4 = i_value;
		if (i_row == 2 && i_col == 3)
			r3c4 = i_value;
		if (i_row == 3 && i_col == 3)
			r4c4 = i_value;
	}

	float Matrix4x4::Get4x4Determinate()
	{
		return this->GetValue(0,0) * this->Get4x4CofactorDeterminate(0,0) -
			this->GetValue(1, 0) * this->Get4x4CofactorDeterminate(1, 0) +
			this->GetValue(2, 0) * this->Get4x4CofactorDeterminate(2, 0) -
			this->GetValue(3, 0) * this->Get4x4CofactorDeterminate(3, 0);
	}

	float Matrix4x4::Get4x4CofactorDeterminate( int i_dRow, int i_dCol)
	{
		Matrix3x3 d3x3 = Matrix3x3();

		for (int i = 0, k = 0; i < 3; i++, k++)
		{
			for (int j = 0, l = 0; j < 3; j++, l++)
			{
				if (k == i_dRow)
				{
					k++;
				}
				if (l == i_dCol)
				{
					l++;
				}

				d3x3.SetValue(i, j, this->GetValue(k,l));
			}
		}

		 
		return d3x3.Get3x3Determinate();
	}

	Matrix4x4 Matrix4x4::Tranpose()
	{
		return Matrix4x4(
			this->GetValue(0, 0), this->GetValue(1, 0), this->GetValue(2, 0), this->GetValue(3, 0),
			this->GetValue(0, 1), this->GetValue(1, 1), this->GetValue(2, 1), this->GetValue(3, 1),
			this->GetValue(0, 2), this->GetValue(1, 2), this->GetValue(2, 2), this->GetValue(3, 2),
			this->GetValue(0, 3), this->GetValue(1, 3), this->GetValue(2, 3), this->GetValue(3, 3)
		);
	}

	Matrix4x4 Matrix4x4::Invert()
	{
		float determinant = this->Get4x4Determinate();
		Matrix4x4 adjunct = Matrix4x4(
			this->Get4x4CofactorDeterminate(0, 0), this->Get4x4CofactorDeterminate(0, 1), this->Get4x4CofactorDeterminate(0, 2), this->Get4x4CofactorDeterminate(0, 3),
			this->Get4x4CofactorDeterminate(1, 0), this->Get4x4CofactorDeterminate(1, 1), this->Get4x4CofactorDeterminate(1, 2), this->Get4x4CofactorDeterminate(1, 3),
			this->Get4x4CofactorDeterminate(2, 0), this->Get4x4CofactorDeterminate(2, 1), this->Get4x4CofactorDeterminate(2, 2), this->Get4x4CofactorDeterminate(2, 3),
			this->Get4x4CofactorDeterminate(3, 0), this->Get4x4CofactorDeterminate(3, 1), this->Get4x4CofactorDeterminate(3, 2), this->Get4x4CofactorDeterminate(3, 3)
		);

		return adjunct /= determinant;
	}
}

