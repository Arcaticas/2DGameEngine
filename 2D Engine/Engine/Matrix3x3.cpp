#include "Matrix3x3.h"

Matrix::Matrix3x3::Matrix3x3() :
	r1c1(0), r1c2(0), r1c3(0),
	r2c1(0), r2c2(0), r2c3(0),
	r3c1(0), r3c2(0), r3c3(0)
{
}

Matrix::Matrix3x3::Matrix3x3(float i_r1c1, float i_r1c2, float i_r1c3, float i_r2c1, float i_r2c2, float i_r2c3, float i_r3c1, float i_r3c2, float i_r3c3) :
	r1c1(i_r1c1), r1c2(i_r1c2), r1c3(i_r1c3),
	r2c1(i_r2c1), r2c2(i_r2c2), r2c3(i_r2c3), 
	r3c1(i_r3c1), r3c2(i_r3c2), r3c3(i_r3c3)
{
}

float Matrix::Matrix3x3::GetValue(int i_row, int i_col)
{
	if ((i_col > 2 || i_col < 0) || (i_row > 2 || i_row < 0))
		return 0.0f;

	if (i_row == 0 && i_col == 0)
		return r1c1;
	if (i_row == 1 && i_col == 0)
		return r2c1;
	if (i_row == 2 && i_col == 0)
		return r3c1;

	if (i_row == 0 && i_col == 1)
		return r1c2;
	if (i_row == 1 && i_col == 1)
		return r2c2;
	if (i_row == 2 && i_col == 1)
		return r3c2;

	if (i_row == 0 && i_col == 2)
		return r1c3;
	if (i_row == 1 && i_col == 2)
		return r2c3;
	if (i_row == 2 && i_col == 2)
		return r3c3;

	return 0;
}

void Matrix::Matrix3x3::SetValue(int i_row, int i_col, float i_value)
{
	if ((i_col > 2 || i_col < 0) || (i_row > 2 || i_row < 0))
		return;

	if (i_row == 0 && i_col == 0)
		r1c1 = i_value;
	if (i_row == 1 && i_col == 0)
		r2c1 = i_value;
	if (i_row == 2 && i_col == 0)
		r3c1 = i_value;

	if (i_row == 0 && i_col == 1)
		r1c2 = i_value;
	if (i_row == 1 && i_col == 1)
		r2c2 = i_value;
	if (i_row == 2 && i_col == 1)
		r3c2 = i_value;

	if (i_row == 0 && i_col == 2)
		r1c3 = i_value;
	if (i_row == 1 && i_col == 2)
		r2c3 = i_value;
	if (i_row == 2 && i_col == 2)
		r3c3 = i_value;
}

float Matrix::Matrix3x3::Get3x3Determinate()
{
	float determinate =
		(this->GetValue(0, 0) * this->GetValue(1, 1) * this->GetValue(2, 2)) +
		(this->GetValue(0, 1) * this->GetValue(1, 2) * this->GetValue(2, 0)) +
		(this->GetValue(0, 2) * this->GetValue(1, 0) * this->GetValue(2, 1)) -
		(this->GetValue(0, 2) * this->GetValue(1, 1) * this->GetValue(2, 0)) -
		(this->GetValue(0, 1) * this->GetValue(1, 0) * this->GetValue(2, 2)) -
		(this->GetValue(0, 0) * this->GetValue(1, 2) * this->GetValue(2, 1));
	return determinate;
}
