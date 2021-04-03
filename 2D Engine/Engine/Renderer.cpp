#include "Renderer.h"

namespace Renderer
{
	void Draw(Renderable& i_renderable)
	{
		assert(i_renderable.GetSprite());
		GLib::Point2D location = { i_renderable.GetLocationFromParent().getXPosition(),
			i_renderable.GetLocationFromParent().getXPosition() };
		GLib::Render(*i_renderable.GetSprite(), location, 0, 0);
	}

	void CreateRenderableObj(GameObjectOwner<Physics::TwoDPhysicsObj>& i_owner , GLib::Sprite* i_sprite)
	{
		//Renderable rendTemp = Renderable(i_owner, i_sprite);
	}


}
