#include "Renderer.h"


void Renderer::Draw(Renderable& i_renderable)
{
	assert(i_renderable.GetSprite());
	GLib::Point2D location = { i_renderable.GetLocationFromParent().getXPosition(),
		i_renderable.GetLocationFromParent().getXPosition() };
	GLib::Render(*i_renderable.GetSprite(), location, 0, 0);
}
