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
				assert(pFile != nullptr);

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

	GameObjectOwner<Physics::TwoDPhysicsObj> CreateGameObjectFromJSON(nlohmann::json& i_JSONdata)
	{
		GameObjectOwner<Physics::TwoDPhysicsObj> NewObj;

		if (i_JSONdata.contains("inital position"))
		{
			nlohmann::json Position = i_JSONdata["inital position"];
			assert(Position.is_array());
			assert(Position.size() == 2);
			assert(Position[0].is_number_float() && Position[1].is_number_float());

			NewObj = Physics::CreatePhysicsObject(Position[0], Position[1]);

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
							nlohmann::json Acceleration = Physics.at("acceleration");
							assert(Acceleration.is_array());
							assert(Acceleration.size() == 2);
							assert(Acceleration[0].is_number_float() && Acceleration[1].is_number_float());
							xAccel = Acceleration[0];
							yAccel = Acceleration[1];
						}

						if (Physics.contains("mass"))
						{
							nlohmann::json Mass = Physics.at("mass");
							assert(Mass.is_number_float());
							mass = Mass;
						}

						if (Physics.contains("drag"))
						{
							nlohmann::json Drag = Physics.at("drag");
							assert(Drag.is_number_float());
							drag = Drag;
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
							nlohmann::json Sprite = Render.value<std::string>("sprite","n/a");
							assert(Sprite.is_string());
							Renderer::CreateRenderableObj(NewObj,Sprite);
							
						}
					}

					if (it.key() == "Collidable")
					{
						nlohmann::json Collide = it.value();

						float xExtent = 0;
						float yExtent = 0;
						if (Collide.contains("extent"))
						{
							nlohmann::json Extent = Collide.at("extent");
							assert(Extent.is_array());
							assert(Extent.size() == 2);
							assert(Extent[0].is_number_float() && Extent[1].is_number_float());
							xExtent = Extent[0];
							yExtent = Extent[1];
							Collision::CreateCollidable(NewObj, xExtent, yExtent);

						}
					}
				}

			}
			
		}

		return NewObj;
	}

	GameObjectOwner<Physics::TwoDPhysicsObj> CreateGameObject(const std::string& i_fileName)
	{
		GameObjectOwner<Physics::TwoDPhysicsObj> NewObject;
		std::vector<uint8_t> Contents = LoadFile(i_fileName);

		if (!Contents.empty())
		{
			nlohmann::json JSON = nlohmann::json::parse(Contents);
			NewObject = CreateGameObjectFromJSON(JSON);
		}

		return NewObject;
	}


}