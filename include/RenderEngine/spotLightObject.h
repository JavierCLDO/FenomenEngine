#pragma once
#include <string>
#include "lightObject.h"

namespace fenomen::render {

class SpotLightObject : public LightObject {

public:
	SpotLightObject();

	virtual ~SpotLightObject();

	void create(const std::string& name = "") override;

	/// <summary>
	/// Only usefull if the type of this light is set to SpotLight
	/// </summary>
	/// <param name="innerAngle">: Angle covered by the bright inner cone.</param>
	/// <param name="outerAngle">: Angle covered by the outer cone.</param>
	/// <param name="fallof">:  The rate of falloff between the inner and outer cones. 1.0 means a linear falloff, 
	///							less means slower falloff, higher means faster falloff.</param>
	void setSpotlightRange(float innerAngle, float outerAngle, float fallof);

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