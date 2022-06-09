#include "pch.h"
#include "Components/audioGeometryComponent.h"
#include "entity.h"
#include "SoundEngine/geometry.h"

fenomen::logic::AudioGeometryComponent::AudioGeometryComponent(Entity* owner) : Component(owner),
	geometry(std::make_unique<sound::Geometry>())
{
	bTick = false;
}

fenomen::logic::AudioGeometryComponent::~AudioGeometryComponent()
{
}

void fenomen::logic::AudioGeometryComponent::Init()
{
	geometry->create(6, 24); //Cube is 6 faces 4 vertex each -> 24 vertices
	geometry->setPos(owner->tranform->getPos());
	geometry->setRot(owner->tranform->getForward(), owner->tranform->getUp());
	geometry->setScale(owner->tranform->getScale());
}

void fenomen::logic::AudioGeometryComponent::Update(double deltaTime)
{
	//It will normaly not need to tick 
	geometry->setPos(owner->tranform->getPos());
	geometry->setRot(owner->tranform->getForward(), owner->tranform->getUp());
	geometry->setScale(owner->tranform->getScale());
}

void fenomen::logic::AudioGeometryComponent::Create(Preset preset, float directocclusion, float reverbocclusion, const Vector& halfSize, bool doublesided)
{
	switch (preset)
	{
	case Plane:
		_createPlane(directocclusion, reverbocclusion, halfSize, doublesided);
		break;
	case Cube:
		_createCube(directocclusion, reverbocclusion, halfSize, doublesided);
	default:
		_createPlane(directocclusion, reverbocclusion, halfSize, doublesided);
		break;
	}
}

void fenomen::logic::AudioGeometryComponent::_createPlane(float directocclusion, float reverbocclusion, const Vector& halfSize, bool doublesided)
{
	double X = halfSize.x;
	double Z = halfSize.z;

	std::vector<Vector> vertices = { {-X, 0, -Z}, {-X, 0, Z}, {X, 0, Z}, {X, 0, -Z} };
	geometry->addPlane(directocclusion, reverbocclusion, doublesided, vertices);
}

void fenomen::logic::AudioGeometryComponent::_createCube(float directocclusion, float reverbocclusion, const Vector& halfSize, bool doublesided)
{
	double X = halfSize.x;
	double Y = halfSize.y;
	double Z = halfSize.z;

	//Bottom
	std::vector<Vector> vertices = { {-X, -Y, -Z}, {-X, -Y, Z}, {X, -Y, Z}, {X, -Y, -Z} };
	geometry->addPlane(directocclusion, reverbocclusion, doublesided, vertices);

	//Top
	vertices = { {-X, Y, -Z}, {-X, Y, Z}, {X, Y, Z}, {X, Y, -Z} };
	geometry->addPlane(directocclusion, reverbocclusion, doublesided, vertices);

	//Left
	vertices = { {-X, Y, -Z}, {-X, Y, Z}, {-X, -Y, Z}, {-X, -Y, -Z} };
	geometry->addPlane(directocclusion, reverbocclusion, doublesided, vertices);

	//Right
	vertices = { {X, Y, -Z}, {X, Y, Z}, {X, -Y, Z}, {X, -Y, -Z} };
	geometry->addPlane(directocclusion, reverbocclusion, doublesided, vertices);

	//Front
	vertices = { {-X, -Y, -Z}, {X, -Y, -Z}, {X, Y, -Z}, {-X, Y, -Z} };
	geometry->addPlane(directocclusion, reverbocclusion, doublesided, vertices);

	//Back
	vertices = { {-X, -Y, Z}, {X, -Y, Z}, {X, Y, Z}, {-X, Y, Z} };
	geometry->addPlane(directocclusion, reverbocclusion, doublesided, vertices);
}
