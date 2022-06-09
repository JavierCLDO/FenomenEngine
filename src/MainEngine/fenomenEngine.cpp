#include "pch.h"
#include "fenomenEngine.h"
#include "RenderEngine/renderEngine.h"
#include "SoundEngine/soundEngine.h"
#include "PhysicsEngine/physicsEngine.h"
#include "inputManager.h"
#include "entity.h"

#include "SDL.h"
#include <execution>
#include <chrono>
#include <future>
#include <semaphore>
#include <thread>

#include "Components/transform.h"
#include "Components/meshComponent.h"
#include "Components/directionalLightComponent.h"
#include <Components/cameraComponent.h>
#include "Components/listenerComponent.h"
#include "Components/sourceComponent.h"
#include "Components/audioGeometryComponent.h"
#include "Components/dynamicRigidBodyComponent.h"
#include "Components/staticRigidBodyComponent.h"

std::counting_semaphore<2> sem_update {0};
std::counting_semaphore<1> sem_render{0}, sem_physics{0};

fenomen::FenomenEngine::FenomenEngine(): run(), entities(), entitiesToAdd(), entitiesToRemove(),
	renderEngine(render::RenderEngine::CreateInstance()), 
	soundEngine(sound::SoundEngine::CreateInstance()),
	physicsEngine(physics::PhysicsEngine::CreateInstance()),
	inputManager(std::make_unique<InputManager>())
{
}

fenomen::FenomenEngine::~FenomenEngine()
{
}

int fenomen::FenomenEngine::Init(FenomenEngine::Prioritize type)
{
	int output = 0;

	std::cout << "FenomenEngine::Init\n";

	SDL_Init(SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC);

	if (output = renderEngine.Init() < 0) {
		std::cout << "RenderEngine exited with code" << output << "\n";
		return output;
	}

	int w, h;

	SDL_GetWindowSize(renderEngine.Instance().getSDLWindow(), &w, &h);

	auto physicsInit_task = std::async(std::launch::async,
		[&]() {
			if (output = physicsEngine.Init() < 0) {
				std::cout << "PhysicsEngine exited with code" << output << "\n";
				return output;
			}
		});

	auto soundInit_task = std::async(std::launch::async,
		[&]() {
			if (output = soundEngine.Init("./Assets/") < 0) {
				std::cout << "SoundEngine exited with code" << output << "\n";
			}
		});

	auto inputInit_task = std::async(std::launch::async,
		[&]() {
			if (output = inputManager->Init(w, h) < 0) {
				std::cout << "InputManager exited with code" << output << "\n";
			}

			inputManager->BindAxis("LookHorizontal", this, &FenomenEngine::rotateCamYaw);
			inputManager->BindAxis("LookVertical", this, &FenomenEngine::rotateCamPitch);

			inputManager->BindAxis("Forward", this, &FenomenEngine::moveForward);
			inputManager->BindAxis("Right", this, &FenomenEngine::moveRight);

			inputManager->CreateAxisEvent("Up");
			inputManager->AddKeyPairToAxisEvent("Up", KEY_LCTRL, KEY_SPACE);
			inputManager->BindAxis("Up", this, &FenomenEngine::moveUp);

			inputManager->CreateActionEvent("LightOn");
			inputManager->CreateActionEvent("LightOff");
			inputManager->CreateActionEvent("CreateSphere");

			inputManager->AddKeyToActionEvent("LightOn", InputManager::ActionEventType::KeyDown, KEY_F);
			inputManager->AddKeyToActionEvent("LightOff", InputManager::ActionEventType::KeyDown, KEY_F, KEY_LSHIFT);
			inputManager->AddKeyToActionEvent("CreateSphere", InputManager::ActionEventType::KeyDown, KEY_RETURN);

			inputManager->BindAction("LightOn", this, &FenomenEngine::turnLightOn);
			inputManager->BindAction("LightOff", this, &FenomenEngine::turnLightOff);
			inputManager->BindAction("CreateSphere", this, &FenomenEngine::addSphere);
		});

	physicsInit_task.wait();
	soundInit_task.wait();
	inputInit_task.wait();

	
	{
		entities.push_back(std::make_unique<fenomen::logic::Entity>());
		entities.back()->_addIt(--entities.end());
		entities.back()->tranform->setPos({ 0.0, 0.0, 0.0 });
		entities.back()->tranform->Roll(-1.0);
		auto rc = ADD_AND_GET_COMPONENT(entities.back().get(), fenomen::logic::MeshComponent);
		rc->CreatePlane(400, 400, 2, 2, 2, 2);
		rc->SetDatablock("Marble");
		rc->SetStatic();
		auto geo = ADD_AND_GET_COMPONENT(entities.back().get(), fenomen::logic::AudioGeometryComponent);
		geo->Create(logic::AudioGeometryComponent::Preset::Plane, 0.9f, 0.5f, rc->GetHalfAABBSize(), true);
		auto srb = ADD_AND_GET_COMPONENT(entities.back().get(), fenomen::logic::StaticRigidBodyComponent);
		srb->Create({ 200, 0.1, 200 }, { 0.0, -0.1, 0.0 });

		int entitiesHalf = 16;
		for (int i = -entitiesHalf; i < entitiesHalf; ++i) {
			for (int j = -entitiesHalf; j < entitiesHalf; ++j) {
				entities.push_back(std::make_unique<fenomen::logic::Entity>());
				entities.back()->_addIt(--entities.end());
				entities.back()->tranform->setPos({ double(i), 6.0 + (std::rand() % 5), double(j) });
				auto rc = ADD_AND_GET_COMPONENT(entities.back().get(), fenomen::logic::MeshComponent);
				rc->Create("Sphere1000.mesh");
				rc->SetDatablock("Rocks");
				/*auto source = ADD_AND_GET_COMPONENT(entities.back().get(), fenomen::logic::SourceComponent);
				source->Create("Sounds/drumloop.wav", true);
				source->Play();*/
				/*auto drb = ADD_AND_GET_COMPONENT(entities.back().get(), fenomen::logic::DynamicRigidBodyComponent);
				drb->Create(0.5);*/
			}
		}

		entities.push_back(std::make_unique<fenomen::logic::Entity>());
		entities.back()->_addIt(--entities.end());
		entities.back()->tranform->setPos({ 0.0, 10.0, 0.0 });
		rc = ADD_AND_GET_COMPONENT(entities.back().get(), fenomen::logic::MeshComponent);
		rc->Create("Sphere1000.mesh");
		rc->SetDatablock("Rocks");
		auto source = ADD_AND_GET_COMPONENT(entities.back().get(), fenomen::logic::SourceComponent);
		source->Create("Sounds/drumloop.wav", true);
		source->Play();
		auto drb = ADD_AND_GET_COMPONENT(entities.back().get(), fenomen::logic::DynamicRigidBodyComponent);
		drb->Create(0.5);


		entities.push_back(std::make_unique<fenomen::logic::Entity>());
		entities.back()->_addIt(--entities.end());
		entities.back()->tranform->setPos({ 0.0, 2.5, -4.0 });
		entities.back()->tranform->Pitch(90);
		rc = ADD_AND_GET_COMPONENT(entities.back().get(), fenomen::logic::MeshComponent);
		rc->CreatePlane(20, 5);
		rc->SetStatic();
		geo = ADD_AND_GET_COMPONENT(entities.back().get(), fenomen::logic::AudioGeometryComponent);
		geo->Create(logic::AudioGeometryComponent::Preset::Plane, 0.9f, 0.5f, rc->GetHalfAABBSize(), true);

		entities.push_back(std::make_unique<fenomen::logic::Entity>());
		entities.back()->_addIt(--entities.end());
		camera = entities.back().get();

		auto cam = ADD_AND_GET_COMPONENT(entities.back().get(), logic::CameraComponent);
		cam->Create();
		cam->owner->tranform->setPos({ 0, 3, 15 });
		cam->owner->tranform->LookAt({ 0, 3, 0 });
		ADD_COMPONENT(camera, logic::ListenerComponent);

		entities.push_back(std::make_unique<fenomen::logic::Entity>());
		entities.back()->_addIt(--entities.end());

		lightTest = entities.back().get();
		lightTest->tranform->LookAt({ -1, -1, -1 });
		auto light = ADD_AND_GET_COMPONENT(lightTest, logic::DirectionalLightComponent);
		light->Create();
		light->SetPower(97);
		light->setTick(true);
		light->setAsSun();
	}
	
	return output;
}

void fenomen::FenomenEngine::Run()
{
	run = true;

	std::cout << "FenomenEngine::Init entities\n";

	//Init entities on sec, as some components add ogre3d sceneManager nodes on init, which is not thread safe
	std::for_each(
		entities.begin(), entities.end(),
		[](auto&& item)
		{
			if (item->bActive)
				item->Init();
		}
	);

	std::cout << "FenomenEngine::Run\n";

	std::thread renderThread(&FenomenEngine::_renderThread, this, &renderEngine);
	std::thread physicsThread(&FenomenEngine::_physicsThread, this, &physicsEngine);

	//Para medir fps
	Uint32 t = SDL_GetTicks();
	Uint32 startTick = t;
	Uint32 ticksSinceLastUpdate = t;
	int ticks = 0;  

#if _DEBUG
	int fpsPeriodUpdate = 100;
#else 
	int fpsPeriodUpdate = 1000;
#endif

	//Para medir deltaTime
	auto start = std::chrono::high_resolution_clock::now();
	double deltatime = 0;

	while (run) {

		auto finish = std::chrono::high_resolution_clock::now();
		deltatime = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() * 1e-9;
		start = finish;

		t = SDL_GetTicks();

		if ((++ticks) % fpsPeriodUpdate == 0) {
			std::cout << "fps: " << 1000.0 * fpsPeriodUpdate / (t - ticksSinceLastUpdate) << '\n';
			ticksSinceLastUpdate = t;
		}
		
		//Input & logic on main thread (1 thread by SDL)		-> 1 thread
		run = inputManager->Update(deltatime);
			
		_updateEntities(deltatime);

		sem_physics.release();
		sem_render.release();

		//Sound on main thread (this + 2 main threads)				-> 3 threads
		soundEngine.Update();

		//Twice (1 for renderThread, 1 for physicsThread)
		sem_update.acquire();
		sem_update.acquire();

		//Sync physics
		_syncEntities();

		//Erase & and entities
		_purgeEntities();
		_addEntities();

		if (!renderEngine.isRenderWindowVisible()) {

			SDL_Delay(200);
		}
	}

	std::cout << "\naverage fps: " << 1000.0 * ticks / (SDL_GetTicks() - startTick) << '\n';
	std::cout << "average ms per frame: " << (SDL_GetTicks() - startTick) / double(ticks) << '\n';

	sem_physics.release();
	sem_render.release();

	renderThread.join();
	physicsThread.join();

	Close();
}

fenomen::logic::Entity* fenomen::FenomenEngine::addEntity()
{
	entitiesToAdd.push_back(std::make_unique<logic::Entity>());

	return entitiesToAdd.back().get();
}

void fenomen::FenomenEngine::destroyEntity(logic::Entity* e)
{
	entitiesToRemove.push_back(e->_it);
}

void fenomen::FenomenEngine::_renderThread(render::RenderEngine* renderEngine)
{
	//Para medir deltaTime
	auto start = std::chrono::high_resolution_clock::now();
	double deltatime = 0;

	std::cout << "started render thread\n";

	while (run) {
		sem_render.acquire();

		auto finish = std::chrono::high_resolution_clock::now();
		deltatime = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() * 1e-9;
		start = finish;

		renderEngine->draw(deltatime);

		sem_update.release();
	}
}

void fenomen::FenomenEngine::_physicsThread(physics::PhysicsEngine* physicsEngine)
{
	//Para medir deltaTime
	auto start = std::chrono::high_resolution_clock::now();
	double deltatime = 0;

	std::cout << "started physics thread\n";

	while (run) {
		sem_physics.acquire();

		auto finish = std::chrono::high_resolution_clock::now();
		deltatime = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() * 1e-9;
		start = finish;

		physicsEngine->Update(deltatime);

		sem_update.release();
	}
}


void fenomen::FenomenEngine::_purgeEntities()
{
	for (auto &it : entitiesToRemove) {
		(*it)->OnDestroy();
		entities.erase(it);
	}
	entitiesToRemove.clear();
}

void fenomen::FenomenEngine::_addEntities()
{
	for (auto& e : entitiesToAdd) {
		e->_addIt(entities.insert(entities.end(),std::move(e)));	
		entities.back()->Init();
	}
	entitiesToAdd.clear();
}

void fenomen::FenomenEngine::_syncEntities()
{
	std::for_each(
		std::execution::seq,
		entities.begin(),
		entities.end(),
		[](auto&& item)
		{
			if (item->bActive)
				item->Sync();
		}
	);
}

void fenomen::FenomenEngine::turnLightOff()
{
	lightTest->getComponent<fenomen::logic::DirectionalLightComponent>()->SetPower(2);
}

void fenomen::FenomenEngine::turnLightOn()
{
	lightTest->getComponent<fenomen::logic::DirectionalLightComponent>()->SetPower(96);
}

void fenomen::FenomenEngine::addSphere()
{
	auto e = addEntity(); 

	double randX = 0.5 - (std::rand() % 32) / 32.0;
	double randZ = 0.5 - (std::rand() % 32) / 32.0;

	e->tranform->setPos({ -1.8 + randX, 8.0, -1.0 + randZ });
	auto rc = ADD_AND_GET_COMPONENT(e, fenomen::logic::MeshComponent);

	if (std::rand() % 2 == 0) {
		rc->Create("Sphere1000.mesh");
		auto drb = ADD_AND_GET_COMPONENT(e, fenomen::logic::DynamicRigidBodyComponent);
		drb->Create(0.5);
	} 
	else {
		rc->Create("Cube_d.mesh");
		auto drb = ADD_AND_GET_COMPONENT(e, fenomen::logic::DynamicRigidBodyComponent);
		drb->Create(rc->GetHalfAABBSize());
	}
	rc->SetDatablock("Rocks");
	rc->setTick(true);
	auto source = ADD_AND_GET_COMPONENT(e, fenomen::logic::SourceComponent);
	source->Create("Sounds/drumloop.wav", true);
	source->Play();
	
	
}

void fenomen::FenomenEngine::rotateCamYaw(double deltaTime, double amount)
{
	camera->tranform->Yaw(deltaTime * amount * 360, false);
}

void fenomen::FenomenEngine::rotateCamPitch(double deltaTime, double amount)
{
	camera->tranform->Pitch(deltaTime * amount * 360);
}

void fenomen::FenomenEngine::moveForward(double deltaTime, double amount)
{
	camera->tranform->MoveForwardGlobal(deltaTime * amount * 10);
}

void fenomen::FenomenEngine::moveRight(double deltaTime, double amount)
{
	camera->tranform->MoveRightGlobal(deltaTime * amount * 10);
}

void fenomen::FenomenEngine::moveUp(double deltaTime, double amount)
{
	camera->tranform->MoveUpGlobal(deltaTime * amount * 10);
}


void fenomen::FenomenEngine::_updateEntities(double deltaTime)
{
	std::for_each(
		std::execution::seq,
		entities.begin(),
		entities.end(),
		[&deltaTime](auto&& item)
		{
			if (item->bActive)
				item->Update(deltaTime);
		}
	);
}

int fenomen::FenomenEngine::Close()
{
	entities.clear();
	entitiesToAdd.clear();
	entitiesToRemove.clear();

	renderEngine.Close();
	soundEngine.Close();
	physicsEngine.Close();

	SDL_Quit();

	std::cout << "FenomenEngine::Exit successfull\n";
	return 0;
}
