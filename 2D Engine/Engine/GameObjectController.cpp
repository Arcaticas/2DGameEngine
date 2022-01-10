#include "GameObjectController.h"


namespace Engine
{
	std::vector<GameObjectOwner<Physics::TwoDPhysicsObj>>& AllGameObjects = *(new std::vector<GameObjectOwner<Physics::TwoDPhysicsObj>>());
	std::vector<GameObjectOwner<Physics::TwoDPhysicsObj>>& NewGameObjects = *(new std::vector<GameObjectOwner<Physics::TwoDPhysicsObj>>());


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
	void DeleteObject(GameObjectOwner<Physics::TwoDPhysicsObj>& i_ptr)
	{
		int index = 0;
		for (Renderer::Renderable it : Renderer::AllRenderablesObjects)
		{
			GameObjectOwner<Physics::TwoDPhysicsObj> temp = it.GetObserver().CreateOwner<Physics::TwoDPhysicsObj>();
			if (temp == i_ptr)
			{
				Renderer::AllRenderablesObjects.erase(Renderer::AllRenderablesObjects.begin()+index);
				break;
			}
			index++;
		}
		index = 0;
		for (Collision::Collidable it : Collision::AllCollidables)
		{
			GameObjectOwner<Physics::TwoDPhysicsObj> temp = it.GetObserver().CreateOwner<Physics::TwoDPhysicsObj>();
			if (temp == i_ptr)
			{
				Collision::AllCollidables.erase(Collision::AllCollidables.begin() + index);
				break;
			}
			index++;
		}
		index = 0;
		for (GameObjectOwner<Physics::TwoDPhysicsObj> it : Engine::AllGameObjects)
		{
			if (it == i_ptr)
			{
				AllGameObjects.erase(Engine::AllGameObjects.begin() + index);
				break;
			}
			index++;
		}
	}
	void ClearObjects()
	{
		CheckForNewGameObjects();
		delete &NewGameObjects;
		AllGameObjects.clear();
		delete &AllGameObjects;
	}
}