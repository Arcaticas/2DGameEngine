#pragma once
#include "Point2D.h"
#include "GLib.h"
#include "GameObjectOwner.h"
#include "GameObjectObserver.h"
#include "2DPhysicsObj.h"


namespace Renderer
{
	class Renderable
	{
	public:
		Renderable(GameObjectObserver<Physics::TwoDPhysicsObj>& i_owner, GLib::Sprite* i_sprite);

		Point2D GetLocationFromParent();
		inline GLib::Sprite* GetSprite();
	private:
		GameObjectObserver<Physics::TwoDPhysicsObj> m_owner;
		GLib::Sprite* m_sprite;
	};
}

#include "Renderable-inl.h"