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

Point2D::Point2D(int x, int y) 
{
	_x = x;
	_y = y;
	xVector = 0;
	yVector = 0;
}

Point2D::Point2D(int x, int y, int xV, int yV)
{
	_x = x;
	_y = y;
	xVector = xV;
	yVector = yV;
}

//Member Overloads
Point2D Point2D::operator+=(Point2D p)
{
	return Point2D(_x + p.getXPosition(), _y + p.getYPosition());
}

Point2D Point2D::operator-=(Point2D p)
{
	return Point2D(_x - p.getXPosition(), _y - p.getYPosition())
}

Point2D Point2D::operator*=(int i)
{
	return Point2D(_x * i, _y * i);
}

Point2D Point2D::operator/=(int i)
{
	return Point2D(_x / i, _y / i);
}

Point2D Point2D::operator-()
{
	return Point2D(-_x, -_y);
}


//Normal Function Overloads
bool operator==(Point2D a, Point2D b)
{
	return a.getXPosition() == b.getXPosition() && a.getYPosition() == b.getYPosition();
}

bool operator!=(Point2D a, Point2D b)
{
	return !(a == b);
}

Point2D operator+(Point2D a, Point2D b) 
{
	return Point2D(a.getXPosition() + b.getXPosition(), a.getYPosition() + b.getYPosition());
}

Point2D operator-(Point2D a, Point2D b)
{
	return Point2D(a.getXPosition() - b.getXPosition(), a.getYPosition() - b.getYPosition());
}

Point2D operator*(Point2D p, int i)
{
	return Point2D(p.getXPosition() * i, p.getYPosition() * i);
}

Point2D operator*(int i, Point2D p)
{
	return Point2D(p.getXPosition() * i, p.getYPosition() * i);
}

Point2D operator/(Point2D p, int i)
{
	return Point2D(p.getXPosition() / i, p.getYPosition() / i);
}
