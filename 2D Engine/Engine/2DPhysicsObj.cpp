#include "2DPhysicsObj.h"


namespace Physics {

	Physics::TwoDPhysicsObj::TwoDPhysicsObj()
	{
		posAndVec.setXPosition(0);
		posAndVec.setYPosition(0);
		posAndVec.setXVector(0);
		posAndVec.setYVector(0);
		xAcceleration = 0;
		yAcceleration = 0;
		mass = 1;
	}

	Physics::TwoDPhysicsObj::TwoDPhysicsObj(float i_xP, float i_yP)
	{
		posAndVec.setXPosition(i_xP);
		posAndVec.setYPosition(i_yP);
		posAndVec.setXVector(0);
		posAndVec.setYVector(0);
		xAcceleration = 0;
		yAcceleration = 0;
		mass = 1;
	}

	TwoDPhysicsObj::TwoDPhysicsObj(float i_xP, float i_yP, float i_xV, float i_yV)
	{
		posAndVec.setXPosition(i_xP);
		posAndVec.setYPosition(i_yP);
		posAndVec.setXVector(i_xV);
		posAndVec.setYVector(i_yV);
		xAcceleration = 0;
		yAcceleration = 0;
		mass = 1;
	}

	Physics::TwoDPhysicsObj::TwoDPhysicsObj(float i_xP, float i_yP, float i_mass)
	{
		posAndVec.setXPosition(i_xP);
		posAndVec.setYPosition(i_yP);
		posAndVec.setXVector(0);
		posAndVec.setYVector(0);
		xAcceleration = 0;
		yAcceleration = 0;
		mass = i_mass;
	}
	TwoDPhysicsObj::TwoDPhysicsObj(float i_xP, float i_yP, float i_xV, float i_yV, float i_mass)
	{
		posAndVec.setXPosition(i_xP);
		posAndVec.setYPosition(i_yP);
		posAndVec.setXVector(i_xV);
		posAndVec.setYVector(i_yV);
		xAcceleration = 0;
		yAcceleration = 0;
		mass = i_mass;
	}
}

