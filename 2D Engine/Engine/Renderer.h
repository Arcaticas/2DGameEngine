#pragma once
#include <vector>
#include "Renderable.h"
#include "GameObjectOwner.h"

namespace Renderer
{
	static std::vector<Renderable> AllRenderableObjects;

	void Draw(Renderable& i_renderable);
	void CreateRenderableObj(GameObjectOwner<Physics::TwoDPhysicsObj>& i_owner, GLib::Sprite* i_sprite);
	Renderable GetRenderable(GameObjectOwner<Physics::TwoDPhysicsObj>& i_owner);
}