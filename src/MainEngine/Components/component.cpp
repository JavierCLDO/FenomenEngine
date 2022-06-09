#include "pch.h"
#include "Components/component.h"


fenomen::logic::Component::Component(Entity* owner) : bTick(false), bActive(true), owner(owner)
{
}

fenomen::logic::Component::~Component()
{
}
