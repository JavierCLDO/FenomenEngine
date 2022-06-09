#include "pch.h"
#include "Components/renderComponent.h"
#include "RenderEngine/renderObject.h"
#include "entity.h"
#include "Components/transform.h"

fenomen::logic::RenderComponent::RenderComponent(Entity* owner): Component(owner), 
renderObject(nullptr), bStatic(false), bVisible(true)
{
}

fenomen::logic::RenderComponent::~RenderComponent()
{
}

void fenomen::logic::RenderComponent::Init()
{
	renderObject->initNode();

	renderObject->setPos(owner->tranform->getPos());
	renderObject->setRot(owner->tranform->getRot());
	renderObject->setScale(owner->tranform->getScale());

	renderObject->attachToNode();

	renderObject->setVisible(bVisible);
	if (bStatic) renderObject->setStatic();
	else		 renderObject->setDynamic();
}

void fenomen::logic::RenderComponent::Sync()
{
	if (!bStatic) {
		renderObject->setPos(owner->tranform->getPos());
		renderObject->setRot(owner->tranform->getRot());
		renderObject->setScale(owner->tranform->getScale());
	}
}

void fenomen::logic::RenderComponent::OnDestroy()
{
	renderObject->destroy();
}

void fenomen::logic::RenderComponent::SetVisible(bool b)
{
	bVisible = b;
	renderObject->setVisible(b);
}

void fenomen::logic::RenderComponent::SetStatic()
{
	bStatic = true;
	renderObject->setStatic();
}

void fenomen::logic::RenderComponent::SetDynamic()
{
	bStatic = false;
	renderObject->setDynamic();
}
