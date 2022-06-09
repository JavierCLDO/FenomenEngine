#pragma once

#include "typemap.h"
#include "Components/component.h"
#include "Components/transform.h"
#include <assert.h>

#define ADD_COMPONENT(entity, comp) entity->provideComponent<comp>(std::make_unique<comp>(entity))

#define ADD_AND_GET_COMPONENT(entity, comp) entity->provideAndGetComponent<comp>(std::make_unique<comp>(entity))

namespace fenomen::logic {


class Entity {
public:
	Entity();
	~Entity();

	void Init();
	void Update(double deltaTime);
	void Sync();

	void OnTriggerEnter(Entity* other);
	void OnTriggerExit(Entity* other);

	void OnCollision(Entity* other);
	void OnCollisionSeparated(Entity* other);

	void PositionChanged();
	void RotationChanged();

	std::unique_ptr<Transform> tranform;

protected:
	bool bActive;
	void OnDestroy();

	friend class FenomenEngine;

public:

	template <typename T>
	T* getComponent() {
		static_assert(std::is_base_of<Component, T>::value, "T1 must derive from Base");
		auto it = m_components.find<T>();
		assert(it != m_components.end());
		return static_cast<T*>(it->second.get());
	}

	template <typename T>
	void provideComponent(std::unique_ptr<T>&& c) {
		m_components.put<T>(std::forward<std::unique_ptr<T>>(c));
	}

	template <typename T>
	T* provideAndGetComponent(std::unique_ptr<T>&& c) {
		m_components.put<T>(std::forward<std::unique_ptr<T>>(c));
		return this->getComponent<T>();
	}

private:

	friend class FenomenEngine;

	inline void _addIt(std::list<std::unique_ptr<Entity>>::iterator it) {
		_it = it;
	}

	std::list<std::unique_ptr<Entity>>::iterator _it;

	TypeMap<std::unique_ptr<Component>> m_components;
};

}
