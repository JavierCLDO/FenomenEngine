#pragma once

#include "Components/lightComponent.h"

namespace fenomen::logic {

class DirectionalLightComponent : public LightComponent {
public:
	DirectionalLightComponent(Entity* owner);
	virtual ~DirectionalLightComponent();

	void Init() override;

	virtual void Create(const std::string& name = "") override;

	void setAsSun();

private:
	bool bSun;
};

}
