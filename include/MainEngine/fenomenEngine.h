#pragma once

#include <memory>
#include <vector>
#include <list>
#include <thread>

namespace fenomen::render { class RenderEngine; }
namespace fenomen::sound { class SoundEngine; }
namespace fenomen::physics { class PhysicsEngine; }
namespace fenomen::logic { class Entity; }
namespace fenomen { class InputManager; }

namespace fenomen {

class FenomenEngine {

public:
	typedef enum {
		/**
		This enum defines the flags used in FenomenEngine::Init call
		
		There are some threads that cannot be avoided to create, and such are
			- SDL Input Events (1 thread)
			- FMOD (2 threads)
			- Main thread (1 thread)
			- Render async + Ogre (2 threads)
			- Physics async + PhysX thread (2 threads)

		As such, this engine does not perform as great with a cpu with less than 8 threads (4 cores with hyperthreading is OK)

		If you have a number of threads in between these options, the leftover threads are not used. 

		Default threads asignation
			8 cores ->					10 cores ->					12 cores ->					16 cores ->
				* input		-> 1			* input		-> 1			* input		-> 1			* input		-> 1
				* sound		-> 2			* sound		-> 2			* sound		-> 2			* sound		-> 2
				* logic		-> 1			* logic		-> 1			* logic		-> 1			* logic		-> 2
				* physics	-> 2			* physics	-> 2			* physics	-> 3			* physics	-> 4
				* render	-> 2			* render	-> 4			* render	-> 5			* render	-> 7
		*/
		feDefault			= 0,

		/**
		* Threads asignation prioritizing render
			8 cores ->					10 cores ->					12 cores ->					16 cores ->
				* input		-> 1			* input		-> 1			* input		-> 1			* input		-> 1
				* sound		-> 2			* sound		-> 2			* sound		-> 2			* sound		-> 2
				* logic		-> 1			* logic		-> 1			* logic		-> 1			* logic		-> 1
				* physics	-> 2			* physics	-> 2			* physics	-> 2			* physics	-> 2
				* render	-> 2			* render	-> 4			* render	-> 6			* render	-> 10
		*/
		fePrioritizeRender	= 1,

		/**
		* Threads asignation for a lot of physics simulation
			8 cores ->					10 cores ->					12 cores ->					16 cores ->
				* input		-> 1			* input		-> 1			* input		-> 1			* input		-> 1
				* sound		-> 2			* sound		-> 2			* sound		-> 2			* sound		-> 2
				* logic		-> 1			* logic		-> 1			* logic		-> 1			* logic		-> 2
				* physics	-> 2			* physics	-> 4			* physics	-> 5			* physics	-> 7
				* render	-> 2			* render	-> 2			* render	-> 3			* render	-> 4
		*/
		fePrioritizePhysics = 2
	} Prioritize;

public:
	
	FenomenEngine();
	~FenomenEngine();

	/*
	* flags is used in order to asign threads to each module
	*/
	int Init(Prioritize type = Prioritize::feDefault);

	void Run();

	logic::Entity* addEntity();

	void destroyEntity(logic::Entity* e);

private:

	void _renderThread(render::RenderEngine* renderEngine);
	void _physicsThread(physics::PhysicsEngine* physicsEngine);

	void _updateEntities(double deltaTime);
	void _purgeEntities();
	void _addEntities();
	void _syncEntities();

	void turnLightOff();
	void turnLightOn();
	void addSphere();

	void rotateCamYaw(double deltaTime, double amount);
	void rotateCamPitch(double deltaTime, double amount);

	void moveForward(double deltaTime, double amount);
	void moveRight(double deltaTime, double amount);
	void moveUp(double deltaTime, double amount);

	int Close();

	std::atomic<bool> run;

	logic::Entity* lightTest, *camera;

	// list of entities to add
	std::list<std::unique_ptr<logic::Entity>> entitiesToAdd;

	// list of iterator entities to remove
	std::list<std::list<std::unique_ptr<logic::Entity>>::iterator> entitiesToRemove;

	// list of current active entities
	std::list<std::unique_ptr<logic::Entity>> entities;

	render::RenderEngine& renderEngine;
	sound::SoundEngine& soundEngine;
	physics::PhysicsEngine& physicsEngine;

	std::unique_ptr<InputManager> inputManager;
};

}