#include "Matrix.h"
#include <cassert>

bool TestMatrix()
{
	using namespace Matrix;

	Matrix4x4 A = Matrix4x4(1, 0, 0, 0,
							0, 1, 0, 0,
							0, 0, 1, 0,
							0, 0, 0, 1);

	Matrix4x4 B = Matrix4x4(0, 0, 0, 1,
							0, 0, 1, 0,
							0, 1, 0, 0,
							1, 0, 0, 0);

	Vector4 C = Vector4(1, 0, 1, 0);

	Vector4 D = Vector4(1, 2, 3, 4);

	assert((A+=B) == Matrix4x4(1, 0, 0, 1,
							   0, 1, 1, 0,
							   0, 1, 1, 0,
							   1, 0, 0, 1));

	assert((A-=B) == Matrix4x4(1, 0, 0, -1,
							   0, 1, -1, 0,
							   0, -1, 1, 0,
							   -1, 0, 0, 1));

	assert((A*=2) == Matrix4x4(2, 0, 0, 0,
							   0, 2, 0, 0,
							   0, 0, 2, 0,
							   0, 0, 0, 2));

	assert((B*=D) == Vector4(4,3,2,1));

	assert((A*=B) == Matrix4x4(0, 0, 0, 1,
							   0, 0, 1, 0,
							   0, 1, 0, 0,
							   1, 0, 0, 0));

	assert((A/=2) == Matrix4x4(.5, 0, 0, 0,
							   0, .5, 0, 0,
							   0, 0, .5, 0,
							   0, 0, 0, .5));

	assert( (A*B) == Matrix4x4(0, 0, 0, 1,
							   0, 0, 1, 0,
							   0, 1, 0, 0,
							   1, 0, 0, 0));

	assert((B * D) == Vector4(4, 3, 2, 1));

	assert((C += D) == Vector4(2, 2, 4, 4));

	assert((D -= C) == Vector4(0, 2, 2, 4));

	assert((D *= 2) == Vector4(2, 4, 6, 8));

	assert((D /= 2) == Vector4(.5f, 1, 1.5f, 2));


	return true;
}