#include <iostream>
#include <stdio.h>
#include "Point2D.h"


//Constructors
Point2D::Point2D() :
	m_x(0),
	m_y(0),
	m_xVector(0),
	m_yVector(0)
{
}

Point2D::Point2D(float i_x, float i_y) :
	m_x(i_x),
	m_y(i_y),
	m_xVector(0),
	m_yVector(0)
{
}

Point2D::Point2D(float i_x, float i_y, float i_dX, float i_dY) :
	m_x(i_x),
	m_y(i_y),
	m_xVector(i_dX),
	m_yVector(i_dY)
{
}