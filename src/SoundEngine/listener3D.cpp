#include "pch.h"
#include "listener3D.h"
#include "soundEngine.h"
#include "fmod.hpp"

fenomen::sound::Listener3D::Listener3D()
{
}

fenomen::sound::Listener3D::~Listener3D()
{
}

void fenomen::sound::Listener3D::update(const Vector& pos, const Vector& vel, const Vector& forward, const Vector& up)
{
	FMOD::System* _sys = SoundEngine::Instance().getSystem();

	FMOD_VECTOR v1{ static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(pos.z) };
	FMOD_VECTOR v2{ static_cast<float>(vel.x), static_cast<float>(vel.y), static_cast<float>(vel.z) };
	FMOD_VECTOR v3{ static_cast<float>(forward.x), static_cast<float>(forward.y), static_cast<float>(forward.z) };
	FMOD_VECTOR v4{ static_cast<float>(up.x), static_cast<float>(up.y), static_cast<float>(up.z) };

	_sys->set3DListenerAttributes(0, &v1, &v2, &v3, &v4);
}
