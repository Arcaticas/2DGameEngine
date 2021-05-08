#include "Renderable.h"


Renderer::Renderable::Renderable() :
	m_owner(GameObjectOwner<Physics::TwoDPhysicsObj>()),
	m_sprite(nullptr)
{
}

Renderer::Renderable::Renderable(const GameObjectOwner<Physics::TwoDPhysicsObj>& i_owner, GLib::Sprite* i_sprite) :
	m_owner(i_owner)
{
	
	m_sprite = i_sprite;
}

//Bugged without the creation of a copy constructor
Renderer::Renderable::Renderable(const GameObjectObserver<Physics::TwoDPhysicsObj>& i_observer, GLib::Sprite* i_sprite) :
	m_owner(i_observer)
{
	m_sprite = i_sprite;
}

Point2D Renderer::Renderable::GetLocationFromParent()
{
	GameObjectOwner<Physics::TwoDPhysicsObj> tempOwner = m_owner.CreateOwner<Physics::TwoDPhysicsObj>();
	return tempOwner->posAndVec;
}

