#include "pch.h"

#include "directionalLightObject.h"
#include "renderEngine.h"
#include "OgreLight.h"

fenomen::render::DirectionalLightObject::DirectionalLightObject() : LightObject()
{
}

fenomen::render::DirectionalLightObject::~DirectionalLightObject()
{
}

void fenomen::render::DirectionalLightObject::create(const std::string& name)
{
	LightObject::create(name);

	_objectLight->setType(Ogre::Light::LightTypes::LT_DIRECTIONAL);
}

void fenomen::render::DirectionalLightObject::setAsSun() {

	if(_objectNode)
		RenderEngine::Instance().setAtmosphere(_objectLight);
}
