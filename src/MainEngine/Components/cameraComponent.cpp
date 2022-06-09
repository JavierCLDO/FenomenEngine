#include "pch.h"
#include "Components/cameraComponent.h"

#include "entity.h"

#include "RenderEngine/camera.h"

fenomen::logic::CameraComponent::CameraComponent(Entity* owner): RenderComponent(owner)
{
	renderObject = std::make_unique<render::Camera>();

	bTick = true;
	owner->tranform->LockPitchAt90(true);
}

fenomen::logic::CameraComponent::~CameraComponent()
{
}

void fenomen::logic::CameraComponent::Init()
{
	RenderComponent::Init();

	std::cout << "CameraComponent::Init\n";
}

void fenomen::logic::CameraComponent::Create(const std::string& mesh)
{
	renderObject->create(mesh);
}
