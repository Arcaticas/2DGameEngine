#pragma once
#include "GLib.h"
#include "GameObjectObserver.h"
#include "2DPhysicsObj.h"


namespace Renderer
{
	class Renderable
	{
	public:
		Renderable();
		Renderable(const GameObjectOwner<Physics::TwoDPhysicsObj>& i_owner, GLib::Sprite* i_sprite);
		Renderable(const GameObjectObserver<Physics::TwoDPhysicsObj>& i_observer, GLib::Sprite* i_sprite);

		Point2D GetLocationFromParent();
		inline GameObjectObserver<Physics::TwoDPhysicsObj> GetObserver();
		inline GLib::Sprite* GetSprite();
	private:
		GameObjectObserver<Physics::TwoDPhysicsObj> m_owner;
		GLib::Sprite* m_sprite;
	};
}

#include "Renderable-inl.h"