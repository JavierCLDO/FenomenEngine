#include "pch.h"

#include "pointLightObject.h"
#include "OgreLight.h"

fenomen::render::PointLightObject::PointLightObject() : LightObject()
{
}

fenomen::render::PointLightObject::~PointLightObject()
{
}

void fenomen::render::PointLightObject::create(const std::string& name)
{
	LightObject::create(name);

	_objectLight->setType(Ogre::Light::LightTypes::LT_POINT);
}

void fenomen::render::PointLightObject::setAttenuation(float range, float constant, float linear, float quadratic)
{
	_objectLight->setAttenuation(range, constant, linear, quadratic);
}

