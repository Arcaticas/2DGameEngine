#pragma once

namespace Matrix
{
	class Matrix3x3
	{
	public:
		Matrix3x3();
		Matrix3x3(float i_r1c1, float i_r1c2, float i_r1c3,
				  float i_r2c1, float i_r2c2, float i_r2c3,
				  float i_r3c1, float i_r3c2, float i_r3c3);

		float GetValue(int i_row, int i_col);
		void SetValue(int i_row, int i_col, float i_value);
		float Get3x3Determinate();

	private:
		float r1c1, r1c2, r1c3,
			  r2c1, r2c2, r2c3,
			  r3c1, r3c2, r3c3;
			
	};

}