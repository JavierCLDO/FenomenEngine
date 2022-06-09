#pragma once

#include "Components/renderComponent.h"

namespace fenomen::render {
	class LightObject;
}

namespace fenomen::logic {

class LightComponent : public RenderComponent {
public:
	virtual ~LightComponent();

	virtual void Init();

	virtual void Create(const std::string&) = 0;

protected:
	LightComponent(Entity* owner);

public:

	void SetPower(double power);
	double GetPower() const;

	void SetDiffuse(double r, double g, double b);
	void SetSpecular(double r, double g, double b);
	void SetCastShadows(bool b);
};

}
