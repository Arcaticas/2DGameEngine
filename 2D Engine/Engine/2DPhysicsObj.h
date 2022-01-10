#pragma once
#include "Point2D.h"

namespace Physics {

	class TwoDPhysicsObj
	{

	public:
		Point2D posAndVec;

		TwoDPhysicsObj();
		TwoDPhysicsObj(float i_xP, float i_yP);
		TwoDPhysicsObj(float i_xP, float i_yP, float i_mass);
		TwoDPhysicsObj(float i_xP, float i_yP, float i_xV, float i_yV, float i_mass);
		TwoDPhysicsObj(float i_xP, float i_yP, float i_mass, float i_dragCoef);
		TwoDPhysicsObj(float i_xP, float i_yP, float i_xV, float i_yV, float i_mass, float i_dragCoef);

		bool operator==(const TwoDPhysicsObj& i_other);
		bool operator!=(const TwoDPhysicsObj& i_other);

		float GetZRotation() { return m_zRotation; }
		float GetXAcceleration() { return m_xAcceleration; }
		float GetYAcceleration() { return m_yAcceleration; }
		float GetMass() { return m_mass; }
		float GetDragCoefficient() { return m_dragCoef; }

		void setZRotation(float i_z) { m_zRotation = i_z; }
		void SetXAcceleration(float i_x) { m_xAcceleration = i_x; }
		void SetYAcceleration(float i_y) { m_yAcceleration = i_y; }
		void SetMass(float i_mass) { m_mass = i_mass; }
		void SetDragCoefficient(float i_dragCoef) { m_dragCoef = i_dragCoef; }
		inline void SetDragCoefficient(float i_fluidDensity, float i_fluidDrag, float i_size);


	private:
		float m_zRotation;
		float m_xAcceleration;
		float m_yAcceleration;
		float m_mass;
		float m_dragCoef;
	};

}

#include "2DPhysicsObj-inl.h"




