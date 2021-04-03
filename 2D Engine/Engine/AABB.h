#pragma once
#include "Point2D.h"

struct AABB
{
public:
	Point2D center;
	Point2D extenstion;

	AABB(Point2D i_center, Point2D i_extension)
	{
		center = i_center;
		extenstion = i_extension;
	}
};