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
		if (i_JSONdata.contains("inital position"))
		{
			nlohmann::json Position = i_JSONdata["inital position"];
			assert(Position.is_array());
			assert(Position.size() == 2);
			assert(Position[0].is_number_float() && Position[1].is_number_float());

			GameObjectOwner<Physics::TwoDPhysicsObj> NewObj = Physics::CreatePhysicsObject(Position[0],Position[1]);

			if (i_JSONdata.contains("components"))
			{
				assert(i_JSONdata["components"].is_object());

				for (nlohmann::json::iterator it = i_JSONdata["components"].begin(); it != i_JSONdata["components"].end(); ++it)
				{
					

					if (it.key() == "TwoDPhysicsObj")
					{
						float xAccel = 0;
						float yAccel = 0;
						float mass = 1;
						float drag = 1;
						nlohmann::json Physics = it.value();

						if (Physics.contains("acceleration"))
						{
							nlohmann::json Acceleration = Physics[0];
							assert(Acceleration.is_array());
							assert(Acceleration.size() == 2);
							assert(Acceleration[0].is_number_float() && Acceleration[1].is_number_float());
							xAccel = Acceleration[0];
							yAccel = Acceleration[1];
						}

						if (Physics.contains("mass"))
						{
							nlohmann::json Mass = Physics[1];
							assert(Mass.is_number_float());
							mass = Mass.value();
						}

						if (Physics.contains("drag"))
						{
							nlohmann::json Drag = Physics[2];
							assert(Drag.is_number_float());
							drag = Drag.value();
						}
						NewObj->SetXAcceleration(xAccel);
						NewObj->SetYAcceleration(yAccel);
						NewObj->SetMass(mass);
						NewObj->SetDragCoefficient(drag);
					}

					if (it.key() == "Renderable")
					{
						nlohmann::json Render = it.value();

						if (Render.contains("sprite"))
						{
							assert(Render[0].is_string());

						}
					}
				}

			}
		}
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