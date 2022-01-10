#pragma once

namespace Renderer
{
	inline GameObjectObserver<Physics::TwoDPhysicsObj> Renderable::GetObserver()
	{
		return m_owner;
	}

	inline GLib::Sprite* Renderable::GetSprite()
	{
		return m_sprite;
	}
}