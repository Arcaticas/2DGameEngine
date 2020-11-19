#include "Timing/Timing.h"

#include <stdio.h>
#include <random>

#define USE_RANDOM_DISTRIBUTION
using namespace Engine;

struct Vector4
{
	float w = 0;
	float x = 0;
	float y = 0;
	float z = 0;
};

struct CharacterData
{
    unsigned int    Health;
    unsigned int    Lives;

    unsigned int    Strength;
    unsigned int    Mana;
    unsigned int    Dex;

    double          drag;
    double          mass;

    char            Name[64];
    int* Compenents[16];

};

struct HotData
{
    Vector4 position;
    Vector4 velocity;

    void UpdatePhysics(const Vector4& newVelocity)
    {
        velocity = newVelocity;
        position.w += velocity.w;
        position.x += velocity.x;
        position.y += velocity.y;
        position.z += velocity.z;
    }
};

struct SlowCharacterData
{
    Vector4 position;
    Vector4 velocity;

    unsigned int    Health = 0;
    unsigned int    Lives = 0;

    unsigned int    Strength = 0;
    unsigned int    Mana = 0;
    unsigned int    Dex = 0;

    double          drag = 0;
    double          mass = 0;

    char            Name[64];
    int* Compenents[16];

    void UpdatePhysics(const Vector4& newVelocity)
    {
        velocity = newVelocity;
        position.w += velocity.w;
        position.x += velocity.x;
        position.y += velocity.y;
        position.z += velocity.z;
    }
};

struct FastCharacter
{
    Vector4 position;
    Vector4 velocity;

    CharacterData* slowData;

    void UpdatePhysics(const Vector4& newVelocity)
    {
        velocity = newVelocity;
        position.w += velocity.w;
        position.x += velocity.x;
        position.y += velocity.y;
        position.z += velocity.z;
    }
};

struct SoACharacter
{
    HotData         hot[8192];
    CharacterData   cold[8192];
};


double UpdateCharacters(SlowCharacterData* data)
{
    Timing::tick Start = Engine::Timing::GetCurrentTickCounter();
    for (int i = 0; i < 8192; i++)
    {
        data[i].UpdatePhysics(Vector4{ 1,1,1,1 });
    }
    double SumTime = Timing::GetTimeDiffInMilliseconds(Start, Timing::GetCurrentTickCounter());
    return SumTime;
}

double UpdateFastCharacters(FastCharacter* data)
{
    Timing::tick Start = Engine::Timing::GetCurrentTickCounter();
    for (int i = 0; i < 8192; i++)
    {
        data[i].UpdatePhysics(Vector4{ 1,1,1,1 });
    }
    double SumTime = Timing::GetTimeDiffInMilliseconds(Start, Timing::GetCurrentTickCounter());
    return SumTime;
}

double UpdateSoACharacters(SoACharacter* data)
{
    Timing::tick Start = Engine::Timing::GetCurrentTickCounter();
    for (int i = 0; i < 8192; i++)
    {
        data[0].hot[i].UpdatePhysics(Vector4{ 1,1,1,1 });
    }
    double SumTime = Timing::GetTimeDiffInMilliseconds(Start, Timing::GetCurrentTickCounter());
    return SumTime;
}

int main()
{

    Engine::Timing::Initialize();
    const unsigned int NumRuns = 8192;

    double UpdateCharactersTime = 0.0;
    double UpdateFastCharactersTime = 0.0;
    double UpdateAoSCharactersTime = 0.0;

   
    SlowCharacterData* slowData = new SlowCharacterData[NumRuns];
    FastCharacter* fastData = new FastCharacter[NumRuns];
    SoACharacter* SoAData = new SoACharacter;

    for (int i = 0; i < 1000; i++)
    {
        UpdateCharactersTime += UpdateCharacters(slowData);
        UpdateFastCharactersTime += UpdateFastCharacters(fastData);
        UpdateAoSCharactersTime += UpdateSoACharacters(SoAData);
    }
    
    printf("Update Characters time %fms.\n", UpdateCharactersTime);
    printf("Update FastCharacters time %fms.\n", UpdateFastCharactersTime);
    printf("Update AoSCharacters time %fms.\n", UpdateAoSCharactersTime);

	return 0;
}
