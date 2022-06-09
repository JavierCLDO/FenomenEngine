#pragma once
#include <memory>

namespace physx {
	class PxFoundation;
	class PxPvd;
	class PxPhysics;

	class PxScene;
	class PxMaterial;
	class PxDefaultAllocator;
	class PxDefaultErrorCallback;
	class PxDefaultCpuDispatcher;
}

namespace fenomen::physics {
	class ContactReportCallback;
}

namespace fenomen::physics {

class PhysicsEngine {

public:
	~PhysicsEngine();

	inline static PhysicsEngine& Instance() { return *instance; }

	static PhysicsEngine& CreateInstance();

	int Init();
	void Update(double deltaTime);
	int Close();

	inline physx::PxPhysics* getPhysics() { return mPhysics; }
	inline physx::PxScene* getScene() { return scene; }

private:

	static std::unique_ptr<PhysicsEngine> instance;

	PhysicsEngine();

	physx::PxFoundation* mFoundation;

	physx::PxPvd* mPvd;
	physx::PxPhysics* mPhysics;

	physx::PxMaterial* mMaterial;

	physx::PxScene* scene;

	physx::PxDefaultAllocator* gDefaultAllocatorCallback;
	physx::PxDefaultErrorCallback* gDefaultErrorCallback;
	physx::PxDefaultCpuDispatcher* gDispatcher;

	ContactReportCallback* callback;

};

}