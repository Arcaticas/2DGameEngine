#pragma once
#include "Point2D.h"

namespace Physics {

	class TwoDPhysicsObj
	{

	public:
		Point2D posAndVec;

		TwoDPhysicsObj();
		TwoDPhysicsObj(float i_xP, float i_yP);
		TwoDPhysicsObj(float i_xP, float i_yP, float i_xV, float i_yV);
		TwoDPhysicsObj(float i_xP, float i_yP, float i_mass);
		TwoDPhysicsObj(float i_xP, float i_yP, float i_xV, float i_yV, float i_mass);

		
		float GetXAcceleration() { return xAcceleration; }
		float GetYAcceleration() { return yAcceleration; }
		float GetMass() { return mass; }

		
		void SetXAcceleration(float i_x) { xAcceleration = i_x; }
		void SetYAcceleration(float i_y) { yAcceleration = i_y; }
		void SetMass(float i_mass) { mass = i_mass; }

	private:
		float xAcceleration;
		float yAcceleration;
		float mass;
	};
}


