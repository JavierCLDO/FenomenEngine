#pragma once


namespace fenomen::logic {

	class Entity;

class Component {
public:
	virtual ~Component();

	virtual void Init() = 0;
	virtual void Update(double) {}
	virtual void OnDestroy() {}
	virtual void Sync() {}

	inline void setTick(bool b) { bTick = b; }
	inline void setActive(bool b) { bActive = b; }

	virtual void OnTriggerEnter(Entity* other) {}
	virtual void OnTriggerExit(Entity* other) {}

	virtual void OnCollision(Entity* other) {}
	virtual void OnCollisionSeparated(Entity* other) {}

	Entity* owner;

protected:
	Component(Entity* owner);

	bool bTick;
	bool bActive;

	friend class Entity;
};

}
