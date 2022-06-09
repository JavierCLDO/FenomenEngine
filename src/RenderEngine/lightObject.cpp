#include "pch.h"

#include "lightObject.h"

#include "renderEngine.h"
#include "OgrePrerequisites.h"
#include "OgreSceneManager.h"

#include "OgreItem.h"

fenomen::render::LightObject::LightObject(): RenderObject(),
_objectLight(nullptr)
{
}

fenomen::render::LightObject::~LightObject()
{
}

void fenomen::render::LightObject::create(const std::string& name)
{
	Ogre::SceneManager* sM = RenderEngine::Instance().getSceneManager();

	_objectLight = sM->createLight();
	_objectLight->setCastShadows(true);
	_object = _objectLight;
}

void fenomen::render::LightObject::setPower(double power)
{
	_objectLight->setPowerScale(power);
}


double fenomen::render::LightObject::getPower() const
{
	return _objectLight->getPowerScale();
}

void fenomen::render::LightObject::setDiffuse(double r, double g, double b)
{
	_objectLight->setDiffuseColour(r, g, b);
}

void fenomen::render::LightObject::setSpecular(double r, double g, double b)
{
	_objectLight->setSpecularColour(r, g, b);
}

void fenomen::render::LightObject::setCastShadows(bool b)
{
	_objectLight->setCastShadows(b);
}
