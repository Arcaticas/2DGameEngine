#include <iostream>
#include <stdio.h>
#include "Point2D.h"


//Constructors
Point2D::Point2D() 
{
	_x = 0;
	_y = 0;
	xVector = 0; 
	yVector = 0;
}

Point2D::Point2D(float x, float y) 
{
	_x = x;
	_y = y;
	xVector = 0;
	yVector = 0;
}

Point2D::Point2D(float x, float y, float xV, float yV)
{
	_x = x;
	_y = y;
	xVector = xV;
	yVector = yV;
}