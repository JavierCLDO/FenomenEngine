#include "pch.h"
#include "Components/dynamicRigidBodyComponent.h"
#include "entity.h"
#include "Components/transform.h"

#include "PhysicsEngine/dynamicRigidbody.h"
#include "collisionCallbacks.h"

fenomen::logic::DynamicRigidBodyComponent::DynamicRigidBodyComponent(Entity* owner) : Component(owner),
	rb(std::make_unique<physics::DynamicRigidbody>())
{
}

void fenomen::logic::DynamicRigidBodyComponent::Init()
{
	rb->addToScene(owner, callbacks::OnTriggerEnter, callbacks::OnTriggerExit, callbacks::OnCollision, callbacks::OnCollisionSeparated);
}

fenomen::logic::DynamicRigidBodyComponent::~DynamicRigidBodyComponent()
{
	rb->release();
}

void fenomen::logic::DynamicRigidBodyComponent::Sync()
{
	rb->retrieveState(owner->tranform->getPosRef(), owner->tranform->getRotRef());
}

void fenomen::logic::DynamicRigidBodyComponent::Create(const Vector& halfSize, const Vector& offset)
{
	rb->create(owner->tranform->getPos() + offset, owner->tranform->getRot(), halfSize);
}

void fenomen::logic::DynamicRigidBodyComponent::Create(double radius, const Vector& offset)
{
	rb->create(owner->tranform->getPos() + offset, owner->tranform->getRot(), radius);
}

void fenomen::logic::DynamicRigidBodyComponent::SetStaticFriction(double fr)
{
	rb->setStaticFriction(fr);
}

void fenomen::logic::DynamicRigidBodyComponent::SetDynamicFriction(double fr)
{
	rb->setDynamicFriction(fr);
}

void fenomen::logic::DynamicRigidBodyComponent::SetRestitution(double r)
{
	rb->setRestitution(r);
}

void fenomen::logic::DynamicRigidBodyComponent::EnableTrigger()
{
	rb->setTrigger();
}

void fenomen::logic::DynamicRigidBodyComponent::SetQueries(bool b)
{
	rb->setQueries(b);
}

void fenomen::logic::DynamicRigidBodyComponent::SetCollisions(bool b)
{
	rb->setCollisions(b);
}

void fenomen::logic::DynamicRigidBodyComponent::EnableCollider()
{
	rb->setCollider();
}
