#include "pch.h"

#include "meshObject.h"

#include "renderEngine.h"
#include "OgrePrerequisites.h"
#include "OgreSceneManager.h"

#include "OgreMesh2.h"
#include "OgreSubMesh2.h"
#include "OgreItem.h"


fenomen::render::MeshObject::MeshObject(): RenderObject(), 
_objectItem(nullptr), _meshName(), _meshSize()
{
}

fenomen::render::MeshObject::~MeshObject()
{
}


void fenomen::render::MeshObject::create(const std::string& mesh)
{
	_meshName = mesh;

	Ogre::SceneManager* sM = RenderEngine::Instance().getSceneManager();
	_objectItem = sM->createItem(_meshName);
	_object = _objectItem;

	auto& size = _objectItem->getLocalAabb();
	_meshSize = { size.mHalfSize.x * 2, size.mHalfSize.y * 2, size.mHalfSize.z * 2 };
}

void fenomen::render::MeshObject::createPlane(double width, double height, uint32_t xsegments, uint32_t ysegments, double utile, double vtile)
{
	Ogre::SceneManager* sM = RenderEngine::Instance().getSceneManager();
	_objectItem = RenderEngine::Instance().createPlaneItem(width, height, xsegments, ysegments, utile, vtile);
	_object = _objectItem;

	_meshSize = { width, 0, height };
}


void fenomen::render::MeshObject::setDatablock(const std::string& name)
{
	assert(_objectItem != nullptr);
	_objectItem->setDatablock(name);
}
