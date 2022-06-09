#include "pch.h"

#include "camera.h"

#include "renderEngine.h"
#include "OgrePrerequisites.h"
#include "OgreSceneManager.h"

#include "OgreCamera.h"

fenomen::render::Camera::Camera(): RenderObject(), _objectCamera(nullptr)
{
}

fenomen::render::Camera::~Camera()
{
}

void fenomen::render::Camera::destroy()
{
	RenderEngine::Instance().destroySceneNode(_objectNode);
	RenderEngine::Instance().destroyCamera(_objectCamera);
}

void fenomen::render::Camera::create(const std::string&)
{
	_objectCamera = RenderEngine::Instance().createCamera();
	_object = _objectCamera;
}
