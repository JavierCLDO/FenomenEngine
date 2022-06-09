#include "pch.h"
#include "Components/staticRigidBodyComponent.h"
#include "entity.h"
#include "Components/transform.h"
#include "collisionCallbacks.h"
#include "PhysicsEngine/staticRigidbody.h"

fenomen::logic::StaticRigidBodyComponent::StaticRigidBodyComponent(Entity* owner) : Component(owner),
	rb(std::make_unique<physics::StaticRigidbody>())
{
	bTick = false;
}

void fenomen::logic::StaticRigidBodyComponent::Init()
{
	rb->addToScene(owner, callbacks::OnTriggerEnter, callbacks::OnTriggerExit, callbacks::OnCollision, callbacks::OnCollisionSeparated);
	rb->setRestitution(.9);
}

fenomen::logic::StaticRigidBodyComponent::~StaticRigidBodyComponent()
{
	rb->release();
}

void fenomen::logic::StaticRigidBodyComponent::Create(const Vector& halfSize, const Vector& offset)
{
	rb->create(owner->tranform->getPos() + offset, owner->tranform->getRot(), halfSize);
}

void fenomen::logic::StaticRigidBodyComponent::CreatePlane()
{
	rb->createPlane(owner->tranform->getPos(), owner->tranform->getRot());
}

void fenomen::logic::StaticRigidBodyComponent::Create(double radius, const Vector& offset)
{
	rb->create(owner->tranform->getPos() + offset, owner->tranform->getRot(), radius);
}

void fenomen::logic::StaticRigidBodyComponent::SetStaticFriction(double fr)
{
	rb->setStaticFriction(fr);
}

void fenomen::logic::StaticRigidBodyComponent::SetDynamicFriction(double fr)
{
	rb->setDynamicFriction(fr);
}

void fenomen::logic::StaticRigidBodyComponent::SetRestitution(double r)
{
	rb->setRestitution(r);
}

void fenomen::logic::StaticRigidBodyComponent::EnableTrigger()
{
	rb->setTrigger();
}

void fenomen::logic::StaticRigidBodyComponent::SetQueries(bool b)
{
	rb->setQueries(b);
}

void fenomen::logic::StaticRigidBodyComponent::EnableCollider()
{
	rb->setCollider();
}

void fenomen::logic::StaticRigidBodyComponent::SetCollisions(bool b)
{
	rb->setCollisions(b);
}
