#pragma once

inline Point2D Point2D::operator+=(const Point2D& p)
{
	return Point2D(m_x + p.getXPosition(), m_y + p.getYPosition());
}

inline Point2D Point2D::operator-=(const Point2D& p)
{
	return Point2D(m_x - p.getXPosition(), m_y - p.getYPosition());
}

inline Point2D Point2D::operator*=(const float i)
{
	return Point2D(m_x * i, m_y * i);
}

inline Point2D Point2D::operator/=(const float i)
{
	return Point2D(m_x / i, m_y / i);
}

inline Point2D Point2D::operator-()
{
	return Point2D(-m_x, -m_y);
}

inline bool operator==(const Point2D& a, const Point2D& b)
{
	return a.getXPosition() == b.getXPosition() && a.getYPosition() == b.getYPosition();
}

inline bool operator!=(const Point2D& a, const Point2D& b)
{
	return !(a == b);
}

inline Point2D operator+(const Point2D& a, const Point2D& b)
{
	return Point2D(a.getXPosition() + b.getXPosition(), a.getYPosition() + b.getYPosition());
}

inline Point2D operator-(const Point2D& a, const Point2D& b)
{
	return Point2D(a.getXPosition() - b.getXPosition(), a.getYPosition() - b.getYPosition());
}

inline Point2D operator*(const Point2D& p, const float i)
{
	return Point2D(p.getXPosition() * i, p.getYPosition() * i);
}

inline Point2D operator*(const float i, const Point2D& p)
{
	return Point2D(p.getXPosition() * i, p.getYPosition() * i);
}

inline Point2D operator/(const Point2D& p, const float i)
{
	return Point2D(p.getXPosition() / i, p.getYPosition() / i);
}