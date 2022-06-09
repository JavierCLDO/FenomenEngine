#include "pch.h"
#include "collider.h"
#include "PxShape.h"

fenomen::physics::Collider::Collider() : shape(nullptr),
onTriggerEnterCallback(nullptr), onTriggerExitCallback(nullptr),
onCollisionCallback(nullptr), onCollisionSeparatedCallback(nullptr),
entity(nullptr)
{

}

fenomen::physics::Collider::~Collider()
{
}

void fenomen::physics::Collider::setTrigger()
{
	if (shape) {
		shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
		shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);
	}
}

void fenomen::physics::Collider::setQueries(bool b)
{
	if (shape) {
		shape->setFlag(physx::PxShapeFlag::eSCENE_QUERY_SHAPE, b);
	}
}

void fenomen::physics::Collider::setCollider()
{
	if (shape) {
		shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, false);
		shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, true);
	}
}

void fenomen::physics::Collider::setCollisions(bool b)
{
	if (shape) {
		shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, b);
	}
}
