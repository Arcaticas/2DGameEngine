#pragma once

#ifndef POINT2D
#define POINT2D


class Point2D
{
private:
	int _x, _y, xVector, yVector;

public:
	Point2D();
	Point2D(int, int);
	Point2D(int, int, int, int);

	inline Point2D operator+=(const Point2D& p);
	inline Point2D operator-=(const Point2D& p);
	inline Point2D operator*=(const int);
	inline Point2D operator/=(const int);
	inline Point2D operator-();
	
	void setXPosition(const int i) { _x = i; }
	void setYPosition(const int i) { _y = i; }
	void setXVector(const int i) { xVector = i; }
	void setYVector(const int i) { yVector = i; }

	int getXPosition() const { return _x; }
	int getYPosition() const { return _y; }
	int getXVector() const { return xVector; }
	int getYVector() const { return yVector; }
};

inline bool operator==(const Point2D&, const Point2D&);
inline bool operator!=(const Point2D&, const Point2D&);

inline Point2D operator+(const Point2D&, const Point2D&);
inline Point2D operator-(const Point2D&, const Point2D&);
inline Point2D operator*(const Point2D&, const int);
inline Point2D operator*(const int, const Point2D&);
inline Point2D operator/(const Point2D& , const int);

#include "Point2D-inl.h"
#endif
