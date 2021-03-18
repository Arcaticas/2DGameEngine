#pragma once
#include <json.hpp>
#include "GameObjectOwner.h"


namespace Loader
{
	std::vector<uint8_t> LoadFile(const std::string& fileName);

	GameObjectOwner CreateGameObjectFromJSON(nlohmann::json& i_JSONdata);
	GameObjectOwner CreateGameObject(const std::string& i_fileName);
}