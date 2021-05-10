#pragma once
#include <vector>
#include "JobSystem/JobSystem.h"
#include "Syncronization/Events.h"
#include "HashedString/HashedString.h"
#include "Syncronization/Mutex.h"
#include "Syncronization/ScopeLock.h"
#include "JSON.h"
#include "2DPhysicsObj.h"
#include "GameObjectOwner.h"
#include <iostream>


namespace Engine
{
	extern std::vector<GameObjectOwner<Physics::TwoDPhysicsObj>>& AllGameObjects;
	extern std::vector<GameObjectOwner<Physics::TwoDPhysicsObj>>& NewGameObjects;

	void AddNewGameObject(GameObjectOwner<Physics::TwoDPhysicsObj> i_pNewGameObject);
	void AddMultipleNewGameObjects(std::vector<const std::string>& i_jsonList);
	void CheckForNewGameObjects();
	void ClearObjects();
}