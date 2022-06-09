#include "pch.h"
#include "source3D.h"
#include "soundEngine.h"
#include "fmod.hpp"

fenomen::sound::Source3D::Source3D(): _sound(nullptr), _channel(nullptr)
{
}

fenomen::sound::Source3D::~Source3D()
{
}

void fenomen::sound::Source3D::create(const std::string& filename, bool loop)
{
	_sound = SoundEngine::Instance().createSound(filename);

	if (loop) _sound->setMode(FMOD_LOOP_NORMAL);
	else _sound->setMode(FMOD_LOOP_OFF);

	auto sys = SoundEngine::Instance().getSystem();

	//Play and pause to erase delay
	sys->playSound(_sound, 0, true, &_channel);
}

void fenomen::sound::Source3D::play()
{
	if (!_channel)
		return;

	_channel->setPosition(0, FMOD_TIMEUNIT_MS);
	_channel->setPaused(false);
}

void fenomen::sound::Source3D::stop()
{
	if (!_channel)
		return;

	_channel->setPaused(true);
	_channel->setPosition(0, FMOD_TIMEUNIT_MS);
}


void fenomen::sound::Source3D::pause()
{
	if (!_channel)
		return;

	_channel->setPaused(false);
}

void fenomen::sound::Source3D::resume()
{
	if (!_channel)
		return;

	_channel->setPaused(true);
}

void fenomen::sound::Source3D::setLoop(bool b)
{
	if (!_channel)
		return;

	if (b) _channel->setMode(FMOD_LOOP_NORMAL);
	else _channel->setMode(FMOD_LOOP_OFF);
}

void fenomen::sound::Source3D::set3DMinMaxDistance(double minDist, double maxDist)
{
	_sound->set3DMinMaxDistance(static_cast<float>(minDist), static_cast<float>(maxDist));
}

void fenomen::sound::Source3D::update(const Vector& pos, const Vector& vel)
{
	if (!_channel)
		return;

	FMOD_VECTOR v1{ static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(pos.z) };
	FMOD_VECTOR v2{ static_cast<float>(vel.x), static_cast<float>(vel.y), static_cast<float>(vel.z) };

	_channel->set3DAttributes(&v1, &v2);
}
