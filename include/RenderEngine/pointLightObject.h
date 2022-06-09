#pragma once
#include <string>
#include "lightObject.h"

namespace fenomen::render {

class PointLightObject : public LightObject {

public:
	PointLightObject();

	virtual ~PointLightObject();

	void create(const std::string& name = "") override;

	/// <summary>
	/// Sets attenuation for the light
	/// </summary>
	/// <param name="range">: The absolute upper range of the light in world units.</param>
	/// <param name="constant">: The constant factor in the attenuation formula: 1.0 means never attenuate, 0.0 is complete attenuation.</param>
	/// <param name="linear">: The linear factor in the attenuation formula: 1 means attenuate evenly over the distance.</param>
	/// <param name="quadratic">: The quadratic factor in the attenuation formula: adds a curvature to the attenuation formula.</param>
	void setAttenuation(float range, float constant, float linear, float quadratic);
};

}