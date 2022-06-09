#include "pch.h"
#include "Components/directionalLightComponent.h"
#include "RenderEngine/directionalLightObject.h"

fenomen::logic::DirectionalLightComponent::DirectionalLightComponent(Entity* owner) : LightComponent(owner),
	bSun(false)
{
	renderObject = std::make_unique<render::DirectionalLightObject>();
}

fenomen::logic::DirectionalLightComponent::~DirectionalLightComponent()
{
}

void fenomen::logic::DirectionalLightComponent::Init()
{
	LightComponent::Init();
	
	if(bSun)
		static_cast<fenomen::render::DirectionalLightObject*>(renderObject.get())->setAsSun();
}

void fenomen::logic::DirectionalLightComponent::Create(const std::string& name)
{
	renderObject->create(name);
}

void fenomen::logic::DirectionalLightComponent::setAsSun()
{
	bSun = true;
	static_cast<fenomen::render::DirectionalLightObject*>(renderObject.get())->setAsSun();
}
