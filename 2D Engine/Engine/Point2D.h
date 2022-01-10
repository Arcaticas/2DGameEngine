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
	
	void setXPosition(const float i_x) { m_x = i_x; }
	void setYPosition(const float i_y) { m_y = i_y; }
	void setXVector(const float i_xV) { m_xVector = i_xV; }
	void setYVector(const float i_yV) { m_yVector = i_yV; }

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
