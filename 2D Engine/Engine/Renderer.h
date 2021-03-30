#pragma once
#include <vector>
#include "Renderable.h"
#include "GameObjectOwner.h"

namespace Renderer
{
	static std::vector<Renderable> AllRenderablesObjects;

	void Draw(Renderable& i_renderable);
	GameObjectObserver<Renderable> CreateRenderableObj();
}