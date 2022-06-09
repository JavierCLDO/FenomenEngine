#include "pch.h"
#include "Components/listenerComponent.h"
#include "SoundEngine/listener3D.h"
#include "Components/transform.h"
#include "entity.h"

fenomen::logic::ListenerComponent::ListenerComponent(Entity* owner): Component(owner), 
	listener(std::make_unique<sound::Listener3D>())
{
	bTick = true;
}

fenomen::logic::ListenerComponent::~ListenerComponent()
{
}

void fenomen::logic::ListenerComponent::Update(double deltaTime)
{
	listener->update(
		owner->tranform->getPos(), 
		owner->tranform->getVel(),
		owner->tranform->getForward(), 
		owner->tranform->getUp()
	);
}

