#pragma once

#include "Utils/vector.h"
#include "Components/component.h"
#include <memory>
#include <string>

namespace fenomen::sound {
	class Listener3D;
}

namespace fenomen::logic {

class ListenerComponent : public Component {
public:
	ListenerComponent(Entity* owner);
	virtual ~ListenerComponent();

	void Init() {}
	void Update(double deltaTime);

protected:
	std::unique_ptr<sound::Listener3D> listener;
};

}
