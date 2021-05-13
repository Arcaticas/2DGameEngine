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
}

Collision::Collidable GetCollidable(const GameObjectOwner<Physics::TwoDPhysicsObj>& i_ptr)
{
	for(Collision::Collidable& it : Collision::AllCollidables)
	{
		GameObjectOwner<Physics::TwoDPhysicsObj> temp = it.GetObserver().CreateOwner<Physics::TwoDPhysicsObj>();
		if (temp == i_ptr)
		{
			return it;
		}

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
		std::vector<Point2D> forces2;

		Engine::JobSystem::JobStatus JobStatus;


		GameObjectOwner<Physics::TwoDPhysicsObj> ptr1 = Loader::CreateGameObject("test.json");
		
		Engine::JobSystem::RunJob(
			Engine::JobSystem::GetDefaultQueueName(),
			[]()
			{
				Engine::AddNewGameObject(Loader::CreateGameObject("test.json"));
			},
			&JobStatus
				);
		JobStatus.WaitForZeroJobsLeft();
		Engine::JobSystem::RunJob(
			Engine::JobSystem::GetDefaultQueueName(),
			[]()
			{
				Engine::AddNewGameObject(Loader::CreateGameObject("test2.json"));
			},
			&JobStatus
				);
		JobStatus.WaitForZeroJobsLeft();

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
					forces1.push_back(Point2D(0, -.01f));
				}
				else
				{
					forces1.clear();
				}

				if (dDown)
				{
					forces2.push_back(Point2D(-.001f, -.001f));
				}
				else
				{
					forces2.clear();
				}

				Physics::Update((*ptr1), forces1, frameTime);

				//checks that collsion is detected in someway
				for (Collision::Collidable& it : Collision::AllCollidables)
				{
					Collision::Collidable temp = GetCollidable(ptr1);
					if(!(temp.GetObserver() == it.GetObserver()))
						Collision::IsCollidingSweep(temp, it, frameTime);
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