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

	Vector4 V = Vector4(1, 2, 3, 4);

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

	assert((B*=V) == Vector4(4,3,2,1));

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

	assert((B * V) == Vector4(4, 3, 2, 1));


	return true;
}