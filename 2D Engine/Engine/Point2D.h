#pragma once

#ifndef POINT2D
#define POINT2D


class Point2D
{
public:
	Point2D();
	Point2D(float, float);
	Point2D(float, float, float, float);

	inline Point2D operator+=(const Point2D& p);
	inline Point2D operator-=(const Point2D& p);
	inline Point2D operator*=(const float);
	inline Point2D operator/=(const float);
	inline Point2D operator-();
	
	void setXPosition(const float i) { _x = i; }
	void setYPosition(const float i) { _y = i; }
	void setXVector(const float i) { xVector = i; }
	void setYVector(const float i) { yVector = i; }

	float getXPosition() const { return _x; }
	float getYPosition() const { return _y; }
	float getXVector() const { return xVector; }
	float getYVector() const { return yVector; }

private:
	float _x, _y, xVector, yVector;
};

inline bool operator==(const Point2D&, const Point2D&);
inline bool operator!=(const Point2D&, const Point2D&);

inline Point2D operator+(const Point2D&, const Point2D&);
inline Point2D operator-(const Point2D&, const Point2D&);
inline Point2D operator*(const Point2D&, const float);
inline Point2D operator*(const float, const Point2D&);
inline Point2D operator/(const Point2D& , const float);



#include "Point2D-inl.h"
#endif
