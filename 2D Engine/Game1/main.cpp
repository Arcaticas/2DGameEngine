#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#include <DirectXColors.h>

#include "GameObjectController.h"
#include "JSON.h"
#include "Timing.h"
#include "Collision.h"
#include <MatrixUnitTest.cpp>

bool aDown = false;
bool dDown = false;
bool spaceDown = false;
bool spacePressed = false;


void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
#ifdef _DEBUG
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);
#endif // __DEBUG

	if (i_VKeyID == 65 && bWentDown)
		aDown = true;
	else
		aDown = false;

	if (i_VKeyID == 68 && bWentDown)
		dDown = true;
	else
		dDown = false;

	if (i_VKeyID == 32 && bWentDown)
	{
		spaceDown = true;
	}
	else
	{
		spaceDown = false;
		spacePressed = false;
	}
}

int wWinMain(_In_ HINSTANCE i_hInstance, _In_opt_ HINSTANCE i_hPrevInstance, _In_ LPWSTR i_lpCmdLine, _In_ int i_nCmdShow)
{

	_CrtSetBreakAlloc(216);

	assert(TestMatrix());

	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 1600, 900, true);
	bool tSuccess = Timing::Int();
	Engine::JobSystem::Init();



	if (bSuccess&&tSuccess)
	{
		GLib::SetKeyStateChangeCallback(TestKeyCallback);

		std::vector<Point2D> forces1;
		std::vector<Point2D> rocketForces = { Point2D(10,0) };

		Engine::JobSystem::JobStatus JobStatus;


		GameObjectOwner<Physics::TwoDPhysicsObj> ptr1 = Loader::CreateGameObject("player.json");
		
		for (int i = 0; i < 3; i++)
		{
			Engine::JobSystem::RunJob(
				Engine::JobSystem::GetDefaultQueueName(),
				[]()
				{
					Engine::AddNewGameObject(Loader::CreateGameObject("enemy.json"));
				},
				&JobStatus
					);
			JobStatus.WaitForZeroJobsLeft();

			(*Engine::NewGameObjects.back()).posAndVec.setYPosition((rand() % 1000) - 500.0f);
		}
		

		float frameTime;

		bool bQuit = false;

		do {
			GLib::Service(bQuit);
			if (!bQuit)
			{
				Engine::CheckForNewGameObjects();


				frameTime = Physics::GetFrameTime();

				if (aDown)
				{
					forces1.push_back(Point2D(0, -.2f));
				}
				else if(dDown)
				{
					forces1.push_back(Point2D(0, .2f));
				}
				else
				{
					forces1.clear();
				}

				if (spaceDown  && !spacePressed)
				{
					spacePressed = true;

					Engine::JobSystem::RunJob(
						Engine::JobSystem::GetDefaultQueueName(),
						[]()
						{
							Engine::AddNewGameObject(Loader::CreateGameObject("rocket.json"));
						},
						&JobStatus
							);
					JobStatus.WaitForZeroJobsLeft();
					(*Engine::NewGameObjects.back()).posAndVec.setYPosition((*ptr1).posAndVec.getYPosition()+100);

				}

				Physics::Update(*ptr1, forces1, frameTime);
				for (GameObjectOwner<Physics::TwoDPhysicsObj>& it : Engine::AllGameObjects)
				{
					if (it->GetMass() == 1)
					{
						Physics::Update(*it, rocketForces, frameTime);
						Collision::Collidable temp = Collision::GetCollidable(it);
						if (temp)
						{
							for (Collision::Collidable& tit : Collision::AllCollidables)
							{
								if(!(temp == tit))
								{
									if (Collision::IsCollidingSweep(tit, temp, frameTime))
									{
										Engine::DeleteObject(it);
										GameObjectOwner<Physics::TwoDPhysicsObj> otherTemp = tit.GetObserver().CreateOwner<Physics::TwoDPhysicsObj>();
										Engine::DeleteObject(otherTemp);
										break;
									}
								}
								
							}

						}
						
					}




					if (it->posAndVec.getXPosition() > 800)
					{
						Engine::DeleteObject(it);
					}
					
				}


				//Rendering
				GLib::BeginRendering(DirectX::Colors::Red);
				GLib::Sprites::BeginRendering();
				
				Renderer::DrawAll();

				GLib::Sprites::EndRendering();
				GLib::EndRendering();
			}
		} while (bQuit == false);


		Renderer::Shutdown();
		Collision::Shutdown();
		Physics::Shutdown();
		GLib::Shutdown();
		Engine::ClearObjects();
		Engine::JobSystem::RequestShutdown();
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

	return 0;
}