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
	
	void setXPosition(const float i) { m_x = i; }
	void setYPosition(const float i) { m_y = i; }
	void setXVector(const float i) { m_xVector = i; }
	void setYVector(const float i) { m_yVector = i; }

	float getXPosition() const { return m_x; }
	float getYPosition() const { return m_y; }
	float getXVector() const { return m_xVector; }
	float getYVector() const { return m_yVector; }

private:
	float m_x, m_y, m_xVector, m_yVector;
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
