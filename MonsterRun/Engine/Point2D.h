#pragma once

#ifndef PLAYER
#define PLAYER


class Point2D
{
private:
	int _x, _y, xVector, yVector;

public:
	Point2D();
	Point2D(int, int);
	Point2D(int, int, int, int);

	Point2D operator-();
	Point2D operator+=(Point2D p);
	Point2D operator-=(Point2D p);
	Point2D operator*=(int);
	Point2D operator/=(int);
	

	int getXPosition() { return _x; }
	int getYPosition() { return _y; }
	int getXVector() { return xVector; }
	int getYVector() { return yVector; }
};

bool operator==(Point2D, Point2D);
bool operator!=(Point2D, Point2D);

Point2D operator+(Point2D, Point2D);
Point2D operator-(Point2D, Point2D);
Point2D operator*(Point2D p, int i);
Point2D operator*(int, Point2D);
Point2D operator/(Point2D p, int i);
#endif
