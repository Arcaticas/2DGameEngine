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

//Member Overloads ALL MOVED TO INLINE HEADER
/*
Point2D Point2D::operator+=(const Point2D& p)
{
	return Point2D(_x + p.getXPosition(), _y + p.getYPosition());
}

Point2D Point2D::operator-=(const Point2D& p)
{
	return Point2D(_x - p.getXPosition(), _y - p.getYPosition());
}

Point2D Point2D::operator*=(const int i)
{
	return Point2D(_x * i, _y * i);
}

Point2D Point2D::operator/=(const int i)
{
	return Point2D(_x / i, _y / i);
}

Point2D Point2D::operator-()
{
	return Point2D(-_x, -_y);
}
*/

//Normal Function Overloads ALL MOVED TO INLINE HEADER
/*
bool operator==(const Point2D& a, const Point2D& b)
{
	return a.getXPosition() == b.getXPosition() && a.getYPosition() == b.getYPosition();
}

bool operator!=(const Point2D& a, const Point2D& b)
{
	return !(a == b);
}

Point2D operator+(const Point2D& a, const Point2D& b)
{
	return Point2D(a.getXPosition() + b.getXPosition(), a.getYPosition() + b.getYPosition());
}

Point2D operator-(const Point2D& a, const Point2D& b)
{
	return Point2D(a.getXPosition() - b.getXPosition(), a.getYPosition() - b.getYPosition());
}

Point2D operator*(const Point2D& p, const int i)
{
	return Point2D(p.getXPosition() * i, p.getYPosition() * i);
}

Point2D operator*(const int i, const Point2D& p)
{
	return Point2D(p.getXPosition() * i, p.getYPosition() * i);
}

Point2D operator/(const Point2D& p,const int i)
{
	return Point2D(p.getXPosition() / i, p.getYPosition() / i);
}
*/