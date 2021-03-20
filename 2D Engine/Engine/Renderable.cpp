#include "Renderable.h"

Renderer::Renderable::Renderable(GameObjectObserver<Physics::TwoDPhysicsObj>& i_owner, GLib::Sprite* i_sprite) :
	m_owner(i_owner)
{
	m_sprite = i_sprite;
}

Point2D Renderer::Renderable::GetLocationFromParent()
{
	GameObjectOwner<Physics::TwoDPhysicsObj> tempOwner = m_owner.CreateOwner<Physics::TwoDPhysicsObj>();
	return tempOwner->posAndVec;
}
