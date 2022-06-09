#include "pch.h"
#include "Components/lightComponent.h"
#include "RenderEngine/lightObject.h"

fenomen::logic::LightComponent::LightComponent(Entity* owner): RenderComponent(owner)
{
}

fenomen::logic::LightComponent::~LightComponent()
{
}

void fenomen::logic::LightComponent::Init()
{
	RenderComponent::Init();
}

void fenomen::logic::LightComponent::SetPower(double power)
{
	static_cast<render::LightObject*>(renderObject.get())->setPower(power);
}

double fenomen::logic::LightComponent::GetPower() const
{
	return static_cast<render::LightObject*>(renderObject.get())->getPower();
}

void fenomen::logic::LightComponent::SetDiffuse(double r, double g, double b)
{
	static_cast<render::LightObject*>(renderObject.get())->setDiffuse(r, g, b);
}

void fenomen::logic::LightComponent::SetSpecular(double r, double g, double b)
{
	static_cast<render::LightObject*>(renderObject.get())->setSpecular(r, g, b);
}

void fenomen::logic::LightComponent::SetCastShadows(bool b)
{
	static_cast<render::LightObject*>(renderObject.get())->setCastShadows(b);
}
