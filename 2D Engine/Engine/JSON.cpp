#include "JSON.h"

namespace Loader {


	std::vector<uint8_t> Loader::LoadFile(const std::string& i_fileName)
	{
		std::vector<uint8_t> Contents;

		if (!i_fileName.empty())
		{
			FILE* pFile = nullptr;

			errno_t fopenError = fopen_s(&pFile, i_fileName.c_str(), "rb");

			if (fopenError == 0)
			{
				assert(pFile == nullptr);

				int fileIOError = fseek(pFile, 0, SEEK_END);
				assert(fileIOError == 0);

				long fileSize = ftell(pFile);
				assert(fileSize >= 0);

				fileIOError = fseek(pFile, 0, SEEK_SET);
				assert(fileIOError == 0);

				Contents.reserve(fileSize);
				Contents.resize(fileSize);

				size_t fileRead = fread(&Contents[0], 1, fileSize, pFile);
				assert(fileRead == fileSize);

				fclose(pFile);
			}
		}

		return Contents;
	}

	template <typename T>
	GameObjectOwner<T> CreateGameObjectFromJSON(nlohmann::json& i_JSONdata)
	{
		return GameObjectOwner<T>();
	}

	template <typename T>
	GameObjectOwner<T> CreateGameObject(const std::string& i_fileName)
	{
		std::vector<uint8_t> Contents = LoadFile(i_fileName);

		if (!Contents.empty())
		{

		}

		return GameObjectOwner<T>();
	}


}