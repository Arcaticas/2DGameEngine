#pragma once
#include <json.hpp>
#include <string>
#include "Physics.h"
#include "Renderer.h"



namespace Loader
{
	std::vector<uint8_t> LoadFile(const std::string& fileName);

	GameObjectOwner<Physics::TwoDPhysicsObj> CreateGameObjectFromJSON(nlohmann::json& i_JSONdata);
	GameObjectOwner<Physics::TwoDPhysicsObj> CreateGameObject(const std::string& i_fileName);
}