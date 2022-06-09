#include "pch.h"
#include "staticRigidbody.h"
#include "physicsEngine.h"
#include "PxPhysicsAPI.h"

fenomen::physics::StaticRigidbody::StaticRigidbody(): Collider(),
	rigidbody(nullptr), material(nullptr)
{
}

fenomen::physics::StaticRigidbody::~StaticRigidbody()
{
}

void fenomen::physics::StaticRigidbody::release()
{
	if (rigidbody)
		rigidbody->release();
	
	if (material)
		material->release();
}

void fenomen::physics::StaticRigidbody::_create(const Vector& pos, const Quaternion& rot)
{
	auto p = PhysicsEngine::Instance().getPhysics();

	physx::PxTransform tr;
	tr.p = { static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(pos.z) };
	tr.q = { static_cast<float>(rot.x), static_cast<float>(rot.y), static_cast<float>(rot.z), static_cast<float>(rot.w) };
	rigidbody = p->createRigidStatic(tr);

	material = p->createMaterial(0.5f, 0.5f, 0.5f);
}


void fenomen::physics::StaticRigidbody::createPlane(const Vector& pos, const Quaternion& rot)
{
	auto p = PhysicsEngine::Instance().getPhysics();

	physx::PxTransform tr;
	tr.p = { static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(pos.z) };
	tr.q = { static_cast<float>(rot.x), static_cast<float>(rot.y), static_cast<float>(rot.z), static_cast<float>(rot.w) };
	rigidbody = p->createRigidStatic(tr);

	material = p->createMaterial(0.5f, 0.5f, 0.5f);

	auto q = rot;
	auto up = q * Vector::up;

	auto plane = physx::PxPlane({ static_cast<float>(up.x), static_cast<float>(up.y), static_cast<float>(up.z)}, 0);
	rigidbody = physx::PxCreatePlane(*p, plane, *material);
}

void fenomen::physics::StaticRigidbody::create(const Vector& pos, const Quaternion& rot, const Vector& halfExtents)
{
	_create(pos, rot);

	shape = physx::PxRigidActorExt::createExclusiveShape(*rigidbody, physx::PxBoxGeometry(halfExtents.x, halfExtents.y, halfExtents.z), *material);
	shape->setFlag(physx::PxShapeFlag::eVISUALIZATION, false);
}

void fenomen::physics::StaticRigidbody::create(const Vector& pos, const Quaternion& rot, const double radius)
{
	_create(pos, rot);

	shape = physx::PxRigidActorExt::createExclusiveShape(*rigidbody, physx::PxSphereGeometry(radius), *material);
	shape->setFlag(physx::PxShapeFlag::eVISUALIZATION, false);
}

void fenomen::physics::StaticRigidbody::addToScene(logic::Entity* _entity, 
	Callback* onTriggerEnterCallback, Callback* onTriggerExitCallback,
	Callback* onCollisionCallback, Callback* onCollisionSeparatedCallback)
{
	auto s = PhysicsEngine::Instance().getScene();

	s->addActor(*rigidbody);

	rigidbody->userData = this;
	this->entity = _entity;
	this->onTriggerEnterCallback = onTriggerEnterCallback;
	this->onTriggerExitCallback = onTriggerExitCallback;
	this->onCollisionCallback = onCollisionCallback;
	this->onCollisionSeparatedCallback = onCollisionSeparatedCallback;
}

void fenomen::physics::StaticRigidbody::setStaticFriction(double fr)
{
	material->setStaticFriction(fr);
}

void fenomen::physics::StaticRigidbody::setDynamicFriction(double fr)
{
	material->setDynamicFriction(fr);
}

void fenomen::physics::StaticRigidbody::setRestitution(double r)
{
	material->setRestitution(r);
}
