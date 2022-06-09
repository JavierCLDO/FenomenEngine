#include "pch.h"
#include "Components/meshComponent.h"

#include "entity.h"

#include "RenderEngine/meshObject.h"

fenomen::logic::MeshComponent::MeshComponent(Entity* owner): RenderComponent(owner), bDataBlockChanged(false), dataBlock()
{
	renderObject = std::make_unique<render::MeshObject>();
}

fenomen::logic::MeshComponent::~MeshComponent()
{
}

void fenomen::logic::MeshComponent::Init()
{
	RenderComponent::Init();
}

void fenomen::logic::MeshComponent::SetDatablock(const std::string& name)
{
	dataBlock = name;
	bDataBlockChanged = true;
}

const Vector& fenomen::logic::MeshComponent::GetAABBsize()
{
	return static_cast<fenomen::render::MeshObject*>(renderObject.get())->getAABB();
}

const Vector& fenomen::logic::MeshComponent::GetHalfAABBSize()
{
	return static_cast<fenomen::render::MeshObject*>(renderObject.get())->getHalfAABB();
}

void fenomen::logic::MeshComponent::Sync()
{
	RenderComponent::Sync();
	if (bDataBlockChanged) {
		static_cast<fenomen::render::MeshObject*>(renderObject.get())->setDatablock(dataBlock);
		bDataBlockChanged = false;
	}
}

void fenomen::logic::MeshComponent::Create(const std::string& mesh)
{
	renderObject->create(mesh);
}

void fenomen::logic::MeshComponent::CreatePlane(double width, double height, uint32_t xsegments, uint32_t ysegments, double utile, double vtile)
{
	static_cast<fenomen::render::MeshObject*>(renderObject.get())->createPlane(width, height, xsegments, ysegments, utile, vtile);
}

void fenomen::logic::MeshComponent::Create(const std::string& mesh, const std::string& datablock)
{
	renderObject->create(mesh);
	static_cast<fenomen::render::MeshObject*>(renderObject.get())->setDatablock(datablock);
}