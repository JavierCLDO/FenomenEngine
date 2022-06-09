#pragma once
#include <memory>
#include "vector.h"
#include "quaternion.h"
#include "collider.h"

namespace physx {
	class PxRigidStatic;
	class PxMaterial;
}

namespace fenomen::physics {

class StaticRigidbody: public Collider {

public:
	StaticRigidbody();
	~StaticRigidbody();

	void release();

	/**
	* Plane shaped
	*/
	void createPlane(const Vector& pos, const Quaternion& rot);

	/**
	* Box shaped
	*/
	void create(const Vector& pos, const Quaternion& rot, const Vector& halfExtents);

	/**
	* Sphere shaped
	*/
	void create(const Vector& pos, const Quaternion& rot, const double radius);

	void addToScene(logic::Entity* entity, 
		Callback* onTriggerEnterCallback, Callback* onTriggerExitCallback,
		Callback* onCollisionCallback, Callback* onCollisionSeparatedCallback);

	void setStaticFriction(double fr);
	void setDynamicFriction(double fr);
	void setRestitution(double r);

private:

	void _create(const Vector& pos, const Quaternion& rot);

	physx::PxRigidStatic* rigidbody;

	physx::PxMaterial* material;
};

}