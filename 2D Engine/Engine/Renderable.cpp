#include "Renderable.h"

namespace Renderer
{
	Renderable::Renderable(GameObjectOwner<Physics::TwoDPhysicsObj>& i_owner, GLib::Sprite* i_sprite) :
		m_owner(i_owner)
	{
		m_sprite = i_sprite;
	}

	Point2D Renderable::GetLocationFromParent()
	{
		GameObjectOwner<Physics::TwoDPhysicsObj> tempOwner = m_owner.CreateOwner();
		return tempOwner->posAndVec;
	}

}
