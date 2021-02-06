#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>

#include <DirectXColors.h>

#include "GLib.h"

using namespace GLib;

bool aDown = false;
bool dDown = false;

void* LoadFile(const char* i_pFilename, size_t& o_sizeFile)
{
	assert(i_pFilename != NULL);

	FILE* pFile = NULL;

	errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
	if (fopenError != 0)
		return NULL;

	assert(pFile != NULL);

	int FileIOError = fseek(pFile, 0, SEEK_END);
	assert(FileIOError == 0);

	long FileSize = ftell(pFile);
	assert(FileSize >= 0);

	FileIOError = fseek(pFile, 0, SEEK_SET);
	assert(FileIOError == 0);

	uint8_t* pBuffer = new uint8_t[FileSize];
	assert(pBuffer);

	size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
	assert(FileRead == FileSize);

	fclose(pFile);

	o_sizeFile = FileSize;

	return pBuffer;
}

Sprite* CreateSprite(const char* i_pFilename)
{
	assert(i_pFilename);

	size_t sizeTextureFile = 0;

	// Load the source file (texture data)
	void* pTextureFile = LoadFile(i_pFilename, sizeTextureFile);

	// Ask GLib to create a texture out of the data (assuming it was loaded successfully)
	GLib::Texture* pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;

	// exit if something didn't work
	// probably need some debug logging in here!!!!
	if (pTextureFile)
		delete[] pTextureFile;

	if (pTexture == nullptr)
		return nullptr;

	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int depth = 0;

	// Get the dimensions of the texture. We'll use this to determine how big it is on screen
	bool result = GLib::GetDimensions(*pTexture, width, height, depth);
	assert(result == true);
	assert((width > 0) && (height > 0));

	// Define the sprite edges
	GLib::SpriteEdges	Edges = { -float(width / 2.0f), float(height), float(width / 2.0f), 0.0f };
	GLib::SpriteUVs	UVs = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } };
	GLib::RGBA							Color = { 255, 255, 255, 255 };

	// Create the sprite
	GLib::Sprite* pSprite = GLib::CreateSprite(Edges, 0.1f, Color, UVs, pTexture);

	// release our reference on the Texture
	GLib::Release(pTexture);

	return pSprite;
}

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

void rotateSprite(float& rad)
{
	rad = rad + (3.14 / 18);
}

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	bool bSuccess = Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600, true);

	if (bSuccess)
	{
		SetKeyStateChangeCallback(TestKeyCallback);

		Sprite* sprite1 = CreateSprite("sprites\\PP1.dds");
		Sprite* sprite2 = CreateSprite("sprites\\PP2.dds");

		bool bQuit = false;

		do {

			Service(bQuit);

			if (!bQuit)
			{

				BeginRendering(DirectX::Colors::Red);
				Sprites::BeginRendering();
				
				if (sprite1)
				{
					static float radi1 = 0;
					static Point2D offset1 = { -200.0f,-200.0f };
					if (aDown)
					{
						rotateSprite(radi1);
					}

					Render(*sprite1, offset1, 0.0f, radi1);
				}

				if (sprite2)
				{
					static float radi2 = 0;
					static Point2D offset2 = { -200.0f,-400.0f };
					if (dDown)
					{
						rotateSprite(radi2);
					}
					Render(*sprite2, offset2, 0.0f, radi2);
				}

				

				Sprites::EndRendering();
				EndRendering();
			}
		} while (bQuit == false);

		if (sprite1)
			Release(sprite1);
		if (sprite2)
			Release(sprite2);


		Shutdown();
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

	return 0;
}