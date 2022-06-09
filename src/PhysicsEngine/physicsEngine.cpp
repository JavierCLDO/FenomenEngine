#include "pch.h"
#include "framework.h"
#include "physicsEngine.h"
#include "callbacks.h"

#include "PxPhysicsAPI.h"

#define PVD_HOST "127.0.0.1"

std::unique_ptr<fenomen::physics::PhysicsEngine> fenomen::physics::PhysicsEngine::instance = nullptr;

fenomen::physics::PhysicsEngine::PhysicsEngine(): mFoundation(nullptr), 
    gDefaultAllocatorCallback(nullptr), gDefaultErrorCallback(nullptr), 
    callback(new ContactReportCallback())
{
}


fenomen::physics::PhysicsEngine::~PhysicsEngine()
{
}

fenomen::physics::PhysicsEngine& fenomen::physics::PhysicsEngine::CreateInstance()
{
    if (instance.get() == nullptr) {
        instance.reset(new PhysicsEngine());
    }

    return *instance;
}

int fenomen::physics::PhysicsEngine::Init()
{
    using namespace physx;

    gDefaultErrorCallback = new PxDefaultErrorCallback();
    gDefaultAllocatorCallback = new PxDefaultAllocator();

    mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, *gDefaultAllocatorCallback, *gDefaultErrorCallback);

    if (!mFoundation) {
        std::cout << "PxCreateFoundation failed!\n";
        return -1;
    }

    bool recordMemoryAllocations = true;

    mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation,
        PxTolerancesScale(), recordMemoryAllocations);

    if (!mPhysics) {
        std::cout << "PxCreatePhysics failed!";
        return -1;
    }

    mMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.6f);

    physx::PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
    sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
    gDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
    sceneDesc.cpuDispatcher = gDispatcher;
    sceneDesc.filterShader = contactReportFilterShader;
    sceneDesc.simulationEventCallback = callback;

    scene = mPhysics->createScene(sceneDesc);
    if (!scene) {
        std::cout << "PxSceneDesc failed!";
        return -1;
    }
	return 0;
}

void fenomen::physics::PhysicsEngine::Update(double deltaTime)
{
    scene->simulate(deltaTime);
    scene->fetchResults(true);
}

int fenomen::physics::PhysicsEngine::Close()
{
    scene->release();
    mPhysics->release();
    mFoundation->release();

    delete gDefaultAllocatorCallback;
    delete gDefaultErrorCallback;
    delete callback;
	return 0;
}
