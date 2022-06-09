#include "pch.h"

#include "spotLightObject.h"
#include "OgreLight.h"

fenomen::render::SpotLightObject::SpotLightObject() : LightObject()
{
}

fenomen::render::SpotLightObject::~SpotLightObject()
{
}

void fenomen::render::SpotLightObject::create(const std::string& name)
{
	LightObject::create(name);

	_objectLight->setType(Ogre::Light::LightTypes::LT_SPOTLIGHT);
}

void fenomen::render::SpotLightObject::setSpotlightRange(float innerAngle, float outerAngle, float fallof)
{
	_objectLight->setSpotlightRange(Ogre::Radian(innerAngle), Ogre::Radian(outerAngle), fallof);
}

void fenomen::render::SpotLightObject::setAttenuation(float range, float constant, float linear, float quadratic)
{
	_objectLight->setAttenuation(range, constant, linear, quadratic);
}
