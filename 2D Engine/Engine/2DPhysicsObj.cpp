#include "2DPhysicsObj.h"


namespace Physics {

	Physics::TwoDPhysicsObj::TwoDPhysicsObj()
	{
		xPosition = 0;
		yPosition = 0;
		xVelocity = 0;
		yVelocity = 0;
		xAcceleration = 0;
		yAcceleration = 0;
		mass = 1;
	}

	Physics::TwoDPhysicsObj::TwoDPhysicsObj(float i_xP, float i_yP)
	{
		xPosition = i_xP;
		yPosition = i_yP;
		xVelocity = 0;
		yVelocity = 0;
		xAcceleration = 0;
		yAcceleration = 0;
		mass = 1;
	}

	Physics::TwoDPhysicsObj::TwoDPhysicsObj(float i_xP, float i_yP, float i_mass)
	{
		xPosition = i_xP;
		yPosition = i_yP;
		xVelocity = 0;
		yVelocity = 0;
		xAcceleration = 0;
		yAcceleration = 0;
		mass = i_mass;
	}
}

