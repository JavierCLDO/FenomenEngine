// SoundEngine.cpp : Define las funciones de la biblioteca estática.
//

#include "pch.h"
#include "framework.h"
#include "soundEngine.h"

#include "fmod.hpp"
#include "fmod_errors.h"
#include <stdio.h>
#include <stdlib.h>

std::unique_ptr<fenomen::sound::SoundEngine> fenomen::sound::SoundEngine::instance = nullptr;


#define ERRCHECK(_result) ERRCHECK_fn(_result, __FILE__, __LINE__); \
    if(_result != 0) return -1 \

void ERRCHECK_fn(FMOD_RESULT result, const char* file, int line)
{
    if (result != FMOD_OK)
    {
        printf("%s(%d): FMOD error %d - %s", file, line, result, FMOD_ErrorString(result));
    }
}

fenomen::sound::SoundEngine::SoundEngine(): 
    _system(nullptr)
{
}

fenomen::sound::SoundEngine::~SoundEngine()
{
}

fenomen::sound::SoundEngine& fenomen::sound::SoundEngine::CreateInstance()
{
    if (instance.get() == nullptr) {
        instance.reset(new SoundEngine());
    }

    return *instance;
}

// TODO: Ejemplo de una función de biblioteca
int fenomen::sound::SoundEngine::Init(const std::string& path)
{
    std::cout << "Initializing Sound Engine\n";

    _path = path;

	FMOD_RESULT result;

    result = FMOD::System_Create(&_system);
    ERRCHECK(result);

    result = _system->init(100, FMOD_INIT_3D_RIGHTHANDED, nullptr);
    ERRCHECK(result);

    result = _system->set3DSettings(1.0, 1.0f, 1.0f);
    ERRCHECK(result);

    return result;
}

void fenomen::sound::SoundEngine::Update()
{
    _system->update();
}

int fenomen::sound::SoundEngine::Close()
{
    std::cout << "Closing Sound Engine ...";
    FMOD_RESULT result = _system->close();
    ERRCHECK(result);
    result = _system->release();
    ERRCHECK(result);
    std::cout << " done\n";
    return 0;
}

FMOD::Sound* fenomen::sound::SoundEngine::createSound(const std::string& fileName)
{
    FMOD::Sound* s;
    _system->createSound((_path + fileName).c_str(), FMOD_3D, 0, &s);
    return s;
}

