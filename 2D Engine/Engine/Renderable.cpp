#include "Renderable.h"

Renderer::Renderable::Renderable(GameObjectObserver& i_owner, GLib::Sprite* i_sprite) :
	m_owner(i_owner)
{
	m_sprite = i_sprite;
}

Point2D Renderer::Renderable::GetLocationFromParent()
{
	GameObjectOwner tempOwner = m_owner.CreateOwner();
	return tempOwner.operator->()->posAndVec;
}
