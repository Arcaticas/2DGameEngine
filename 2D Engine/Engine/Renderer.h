#pragma once
#include <vector>
#include <string>
#include <iterator>

#include "Renderable.h"
#include "GameObjectOwner.h"

namespace Renderer
{
	extern std::vector<Renderable>& AllRenderablesObjects;

	void* LoadFile(const char* i_pFilename, size_t& o_sizeFile);
	GLib::Sprite* CreateGSprite(const char* i_pFilename);

	void Draw(Renderable& i_renderable);
	void DrawAll();
	void CreateRenderableObj(GameObjectOwner<Physics::TwoDPhysicsObj>& i_owner, const std::string& i_spriteFile);

	void Shutdown();
}