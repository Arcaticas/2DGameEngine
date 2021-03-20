#pragma once
#include <json.hpp>
#include "GameObjectOwner.h"


namespace Loader
{
	std::vector<uint8_t> LoadFile(const std::string& fileName);

	template <typename T> GameObjectOwner<T> CreateGameObjectFromJSON(nlohmann::json& i_JSONdata);
	template <typename T> GameObjectOwner<T> CreateGameObject(const std::string& i_fileName);
}