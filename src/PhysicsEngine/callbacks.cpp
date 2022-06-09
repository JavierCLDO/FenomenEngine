#include "pch.h"
#include "callbacks.h"
#include <collider.h>

physx::PxFilterFlags fenomen::physics::contactReportFilterShader(physx::PxFilterObjectAttributes attributes0, physx::PxFilterData filterData0, physx::PxFilterObjectAttributes attributes1, physx::PxFilterData filterData1, physx::PxPairFlags& pairFlags, const void* constantBlock, physx::PxU32 constantBlockSize)
{
	PX_UNUSED(attributes0);
	PX_UNUSED(attributes1);
	PX_UNUSED(filterData0);
	PX_UNUSED(filterData1);
	PX_UNUSED(constantBlockSize);
	PX_UNUSED(constantBlock);

	// all initial and persisting reports for everything, with per-point data
	pairFlags = physx::PxPairFlag::eSOLVE_CONTACT 
		| physx::PxPairFlag::eDETECT_DISCRETE_CONTACT
		| physx::PxPairFlag::eNOTIFY_TOUCH_FOUND
		| physx::PxPairFlag::eNOTIFY_TOUCH_LOST
		| physx::PxPairFlag::eNOTIFY_CONTACT_POINTS;

	return physx::PxFilterFlag::eDEFAULT;
}

void fenomen::physics::ContactReportCallback::onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count)
{
	PX_UNUSED(count);
	physx::PxActor* actor1 = pairs->triggerActor;
	physx::PxActor* actor2 = pairs->otherActor;

	if (!actor1 || !actor2)
		return;

	auto c1 = static_cast<Collider*>(actor1->userData);
	auto c2 = static_cast<Collider*>(actor2->userData);

	if (pairs->status == physx::PxPairFlag::eNOTIFY_TOUCH_FOUND) 
		c1->onTriggerEnterCallback(c1->entity, c2->entity);
	else if (pairs->status == physx::PxPairFlag::eNOTIFY_TOUCH_LOST)
		c1->onTriggerExitCallback(c1->entity, c2->entity);
}

void fenomen::physics::ContactReportCallback::onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs)
{
	PX_UNUSED(nbPairs);
	physx::PxActor* actor1 = pairHeader.actors[0];
	physx::PxActor* actor2 = pairHeader.actors[1];

	if (!actor1 || !actor2)
		return;

	auto c1 = static_cast<Collider*>(actor1->userData);
	auto c2 = static_cast<Collider*>(actor2->userData);

	if (pairs->flags.isSet(physx::PxContactPairFlag::eACTOR_PAIR_HAS_FIRST_TOUCH)) {
		c1->onCollisionCallback(c1->entity, c2->entity);
	}
	else if (pairs->flags.isSet(physx::PxContactPairFlag::eACTOR_PAIR_LOST_TOUCH)) {
		c1->onCollisionSeparatedCallback(c1->entity, c2->entity);
	}
}
