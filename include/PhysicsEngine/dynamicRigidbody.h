#pragma once
#include <memory>
#include "vector.h"
#include "quaternion.h"
#include "collider.h"

namespace physx {
	class PxRigidDynamic;
	class PxMaterial;
}

namespace fenomen::physics {

class DynamicRigidbody : public Collider {

public:
	DynamicRigidbody();
	~DynamicRigidbody();

	void release();

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

	/**
	* retrieves position and rot from the physics
	*/
	void retrieveState(Vector& pos, Quaternion& rot);

	void setStaticFriction(double fr);
	void setDynamicFriction(double fr);
	void setRestitution(double r);

private:

	void _create(const Vector& pos, const Quaternion& rot);

	physx::PxRigidDynamic* rigidbody;

	physx::PxMaterial* material;
};

}