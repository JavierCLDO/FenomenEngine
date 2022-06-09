#pragma once

namespace physx {
	class PxShape;
}

namespace fenomen::logic {
	class Entity;
}


namespace fenomen::physics {

class Collider {
public:

	using Callback = void(fenomen::logic::Entity* me, fenomen::logic::Entity* other);

public:
	~Collider();

	void setTrigger();
	void setQueries(bool b);
	void setCollider();
	void setCollisions(bool b);

	Callback* onTriggerEnterCallback;
	Callback* onTriggerExitCallback;
	Callback* onCollisionCallback;
	Callback* onCollisionSeparatedCallback;

	logic::Entity* entity;

protected:
	Collider();

	physx::PxShape* shape;
};

}