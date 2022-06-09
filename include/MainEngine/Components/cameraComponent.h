#pragma once

#include "Components/renderComponent.h"
#include <string>

namespace fenomen::logic {

class CameraComponent : public RenderComponent {
public:
	CameraComponent(Entity* owner);
	virtual ~CameraComponent();

	void Init() override;
	//void Update(double deltaTime) override;

	void Create(const std::string& name = "");
};

}
