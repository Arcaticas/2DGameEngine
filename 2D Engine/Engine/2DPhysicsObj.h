#pragma once

namespace Physics {

	class TwoDPhysicsObj
	{

	public:
		TwoDPhysicsObj();
		TwoDPhysicsObj(float xP, float yP);
		TwoDPhysicsObj(float xP, float yP, float mass);

		float GetXPosition() { return xPosition; }
		float GetYPosition() { return yPosition; }
		float GetXVelocity() { return xVelocity; }
		float GetYVelocity() { return yVelocity; }
		float GetXAcceleration() { return xAcceleration; }
		float GetYAcceleration() { return yAcceleration; }
		float GetMass() { return mass; }

		void SetXPosition(float i_x) { xPosition = i_x; }
		void SetYPosition(float i_y) { yPosition = i_y; }
		void SetXVelocity(float i_x) { xVelocity = i_x; }
		void SetYVelocity(float i_y) { yVelocity = i_y; }
		void SetXAcceleration(float i_x) { xAcceleration = i_x; }
		void SetYAcceleration(float i_y) { yAcceleration = i_y; }
		void SetMass(float i_mass) { mass = i_mass; }

	private:
		float xPosition;
		float yPosition;
		float xVelocity;
		float yVelocity;
		float xAcceleration;
		float yAcceleration;
		float mass;
	};
}


