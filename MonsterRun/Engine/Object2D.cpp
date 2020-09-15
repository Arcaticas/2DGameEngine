#include <stdio.h>
#include "Point2D.h"
#include "Object2D.h"

Object2D::Object2D() 
{
	Point2D();
	name = nullptr;
}

Object2D::Object2D(char* n)
{
	Point2D();
	name = n;
}

Object2D::Object2D(char* n, int xPos, int yPos)
{
	Point2D(xPos, yPos),
	name = n;

}

Object2D::Object2D(char* n, int xPos, int yPos, int xVec, int yVec)
{
	Point2D(xPos,yPos,xVec,yVec),
	name = n;
	
}