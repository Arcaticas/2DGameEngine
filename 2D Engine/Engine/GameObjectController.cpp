#include "GameObjectController.h"


namespace Engine
{
	static std::vector<GameObjectOwner<Physics::TwoDPhysicsObj>>& AllGameObjects = *(new std::vector<GameObjectOwner<Physics::TwoDPhysicsObj>>());
	static std::vector<GameObjectOwner<Physics::TwoDPhysicsObj>>& NewGameObjects = *(new std::vector<GameObjectOwner<Physics::TwoDPhysicsObj>>());


	Engine::Mutex NewGameObjectMutex;


	// This adds a new GameObject to NewGameObjects
	void AddNewGameObject(GameObjectOwner<Physics::TwoDPhysicsObj> i_pNewGameObject)
	{
		if (i_pNewGameObject)
		{
			// Acquire a scoped lock on the mutex
			Engine::ScopeLock Lock(NewGameObjectMutex);

			NewGameObjects.push_back(i_pNewGameObject);
		}
	}

	void AddMultipleNewGameObjects(std::vector<std::string>& i_jsonList)
	{
		for (std::string it : i_jsonList)
		{
			AddNewGameObject(Loader::CreateGameObject(it));
		}
	}

	// This will move GameObjects from NewGameObjects -> AllGameObjects
	void CheckForNewGameObjects()
	{
		Engine::ScopeLock Lock(NewGameObjectMutex);

		if (!NewGameObjects.empty())
		{
			for (GameObjectOwner<Physics::TwoDPhysicsObj> p : NewGameObjects)
			{
				if (p)
				{
					AllGameObjects.push_back(p);
				}
			}

			NewGameObjects.clear();
	}
		}
	void ClearObjects()
	{
		CheckForNewGameObjects();
		delete &NewGameObjects;
		//for (GameObjectOwner<Physics::TwoDPhysicsObj>* p : AllGameObjects)
		//{
		//	if (p)
		//		delete p;
		//}
		AllGameObjects.clear();
		delete &AllGameObjects;
	}
}