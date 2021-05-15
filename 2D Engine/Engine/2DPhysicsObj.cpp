#include "2DPhysicsObj.h"


namespace Physics {

	TwoDPhysicsObj::TwoDPhysicsObj() :
		m_xAcceleration(0),
		m_yAcceleration(0),
		m_mass(1),
		m_dragCoef(.1f),
		m_zRotation(0)
	{
		posAndVec = Point2D();
	}

	TwoDPhysicsObj::TwoDPhysicsObj(float i_xP, float i_yP) :
		m_xAcceleration(0),
		m_yAcceleration(0),
		m_mass(1),
		m_dragCoef(.1f),
		m_zRotation(0)
	{
		posAndVec = Point2D(i_xP, i_yP);
	}

	TwoDPhysicsObj::TwoDPhysicsObj(float i_xP, float i_yP, float i_mass) :
		m_xAcceleration(0),
		m_yAcceleration(0),
		m_mass(i_mass),
		m_dragCoef(.1f),
		m_zRotation(0)
	{
		posAndVec = Point2D(i_xP, i_yP);
	}

	TwoDPhysicsObj::TwoDPhysicsObj(float i_xP, float i_yP, float i_mass, float i_dragCoef) :
		m_xAcceleration(0),
		m_yAcceleration(0),
		m_mass(i_mass),
		m_dragCoef(i_dragCoef),
		m_zRotation(0)
	{
		posAndVec = Point2D(i_xP, i_yP);
	}

	TwoDPhysicsObj::TwoDPhysicsObj(float i_xP, float i_yP, float i_xV, float i_yV, float i_mass) :
		m_xAcceleration(0),
		m_yAcceleration(0),
		m_mass(i_mass),
		m_dragCoef(.1f),
		m_zRotation(0)
	{
		posAndVec = Point2D(i_xP, i_yP, i_xV, i_yV);
	}

	TwoDPhysicsObj::TwoDPhysicsObj(float i_xP, float i_yP, float i_xV, float i_yV, float i_mass, float i_dragCoef) :
		m_xAcceleration(0),
		m_yAcceleration(0),
		m_mass(i_mass),
		m_dragCoef(i_dragCoef),
		m_zRotation(0)
	{
		posAndVec = Point2D(i_xP, i_yP, i_xV, i_yV);
	}

	bool TwoDPhysicsObj::operator==(const TwoDPhysicsObj& i_other)
	{
		return posAndVec == i_other.posAndVec && m_mass == i_other.m_mass && m_dragCoef == i_other.m_dragCoef
			&& m_zRotation == i_other.m_zRotation && m_xAcceleration == i_other.m_xAcceleration && m_yAcceleration == i_other.m_yAcceleration;
	}




}

