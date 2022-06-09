#include "pch.h"
#include "dynamicRigidbody.h"
#include "physicsEngine.h"
#include "PxPhysicsAPI.h"

fenomen::physics::DynamicRigidbody::DynamicRigidbody(): rigidbody(nullptr), material(nullptr)
{
}

fenomen::physics::DynamicRigidbody::~DynamicRigidbody()
{
}

void fenomen::physics::DynamicRigidbody::release()
{
	if (rigidbody)
		rigidbody->release();

	if (material)
		material->release();
}

void fenomen::physics::DynamicRigidbody::_create(const Vector& pos, const Quaternion& rot)
{
	auto p = PhysicsEngine::Instance().getPhysics();

	physx::PxTransform tr;
	tr.p = { static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(pos.z) };
	tr.q = { static_cast<float>(rot.x), static_cast<float>(rot.y), static_cast<float>(rot.z), static_cast<float>(rot.w) };
	rigidbody = p->createRigidDynamic(tr);

	material = p->createMaterial(0.5f, 0.5f, 0.5f);
}


void fenomen::physics::DynamicRigidbody::create(const Vector& pos, const Quaternion& rot, const Vector& halfExtents)
{
	_create(pos, rot);

	Vector aux = halfExtents;

	shape = physx::PxRigidActorExt::createExclusiveShape(*rigidbody, 
		physx::PxBoxGeometry(static_cast<float>(aux.x), static_cast<float>(aux.y), static_cast<float>(aux.z)),
		*material);
}

void fenomen::physics::DynamicRigidbody::create(const Vector& pos, const Quaternion& rot, const double radius)
{
	_create(pos, rot);

	shape = physx::PxRigidActorExt::createExclusiveShape(*rigidbody, physx::PxSphereGeometry(radius), *material);
}

void fenomen::physics::DynamicRigidbody::addToScene(logic::Entity* _entity, 
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

void fenomen::physics::DynamicRigidbody::retrieveState(Vector& pos, Quaternion& rot)
{
	if (rigidbody) {
		auto tr = rigidbody->getGlobalPose();
		pos.x = static_cast<double>(tr.p.x); 
		pos.y = static_cast<double>(tr.p.y);
		pos.z = static_cast<double>(tr.p.z);

		rot.w = static_cast<double>(tr.q.w);
		rot.x = static_cast<double>(tr.q.x);
		rot.y = static_cast<double>(tr.q.y);
		rot.z = static_cast<double>(tr.q.z);
	}
}

void fenomen::physics::DynamicRigidbody::setStaticFriction(double fr)
{
	material->setStaticFriction(fr);
}

void fenomen::physics::DynamicRigidbody::setDynamicFriction(double fr)
{
	material->setDynamicFriction(fr);
}

void fenomen::physics::DynamicRigidbody::setRestitution(double r)
{
	material->setRestitution(r);
}

