#pragma once
#include "Point2D.h"
#include "GameObjectObserver.h"
#include "2DPhysicsObj.h"
#include "Matrix4x4.h"

namespace Collision
{
	class Collidable
	{
	public:

		Collidable(GameObjectOwner<Physics::TwoDPhysicsObj>& i_owner, const Point2D& i_extent);

		void Update();
		GameObjectObserver<Physics::TwoDPhysicsObj> GetObserver() { return m_owner; }

		Point2D GetCenter() { return m_center; }
		Point2D GetExtent() { return m_extent; }

		Matrix::Matrix4x4 GetRotationMatrix();
		Matrix::Matrix4x4 GetTranslationMatrix();
		Matrix::Matrix4x4 GetTransformationMatrix();
		Matrix::Vector4 GetVelocity();

		operator bool();
		bool operator==(const Collidable&);
	private:
		GameObjectObserver<Physics::TwoDPhysicsObj> m_owner;
		Point2D m_center;
		Point2D m_extent;
		bool m_collided;
	};

}