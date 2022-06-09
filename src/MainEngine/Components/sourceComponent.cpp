#include "pch.h"
#include "Components/sourceComponent.h"
#include "SoundEngine/source3D.h"
#include "Components/transform.h"
#include "entity.h"

fenomen::logic::SourceComponent::SourceComponent(Entity* owner) : Component(owner),
	source(std::make_unique<sound::Source3D>()), bPlay(), bLoop(), filepath()
{
}

fenomen::logic::SourceComponent::~SourceComponent()
{
}

void fenomen::logic::SourceComponent::Create(const std::string& filePath, bool loop)
{
	filepath = filePath;
	bLoop = loop;
}

void fenomen::logic::SourceComponent::Init()
{
	source->create(filepath, bLoop);
	if (bPlay)
		source->play();
}

void fenomen::logic::SourceComponent::Sync()
{
	source->update(owner->tranform->getPos(), owner->tranform->getVel());
}

void fenomen::logic::SourceComponent::Play()
{
	bPlay = true;
	source->play();
}

void fenomen::logic::SourceComponent::Stop()
{
	bPlay = false;
	source->stop();
}

void fenomen::logic::SourceComponent::Pause()
{
	bPlay = false;
	source->pause();
}

void fenomen::logic::SourceComponent::Resume()
{
	bPlay = true;
	source->resume();
}

void fenomen::logic::SourceComponent::SetLoop(bool b)
{
	bLoop = b;
	source->setLoop(b);
}

void fenomen::logic::SourceComponent::Set3DMinMaxDistance(double minDist, double maxDist)
{
	source->set3DMinMaxDistance(minDist, maxDist);
}
