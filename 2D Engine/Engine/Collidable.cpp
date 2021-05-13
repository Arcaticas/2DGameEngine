#include "Collidable.h"

namespace Collision {

	Collidable::Collidable(GameObjectOwner<Physics::TwoDPhysicsObj>& i_owner, const Point2D& i_extent) :
		m_owner(i_owner),
		m_collided(false)
	{
		m_center = (i_owner->posAndVec + i_extent)/2;
		m_extent = i_extent;
	}


	Collidable::Collidable(GameObjectOwner<Physics::TwoDPhysicsObj>& i_owner, const Point2D& i_center, const Point2D& i_extent) :
		m_owner(i_owner),
		m_center(i_center),
		m_extent(i_extent),
		m_collided(false)
	{
	}

	Matrix::Matrix4x4 Collidable::GetRotationMatrix()
	{
		GameObjectOwner<Physics::TwoDPhysicsObj> tempOwner = m_owner.CreateOwner<Physics::TwoDPhysicsObj>();
		
		return Matrix::Matrix4x4::CreateRotationZ(tempOwner->GetZRotation());
	}

	Matrix::Matrix4x4 Collidable::GetTranslationMatrix()
	{
		GameObjectOwner<Physics::TwoDPhysicsObj> tempOwner = m_owner.CreateOwner<Physics::TwoDPhysicsObj>();

		return Matrix::Matrix4x4::CreateTranslation(tempOwner->posAndVec.getXPosition(), tempOwner->posAndVec.getYPosition(), 1);
	}

	Matrix::Matrix4x4 Collidable::GetTransformationMatrix()
	{
		GameObjectOwner<Physics::TwoDPhysicsObj> tempOwner = m_owner.CreateOwner<Physics::TwoDPhysicsObj>();

		Matrix::Matrix4x4 rot = GetRotationMatrix();
		Matrix::Matrix4x4 trans = GetTranslationMatrix();
		return rot+=trans;
	}

	Matrix::Vector4 Collidable::GetVelocity()
	{
		GameObjectOwner<Physics::TwoDPhysicsObj> tempOwner = m_owner.CreateOwner<Physics::TwoDPhysicsObj>();
		return Matrix::Vector4(tempOwner->posAndVec.getXVector(), tempOwner->posAndVec.getYVector(), 0, 0);
	}

}

