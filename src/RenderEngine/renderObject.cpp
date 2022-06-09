#include "pch.h"

#include "vector.h"
#include "quaternion.h"

#include "renderObject.h"
#include "renderEngine.h"
#include "OgrePrerequisites.h"
#include "OgreSceneNode.h"
#include "OgreMovableObject.h"

fenomen::render::RenderObject::RenderObject():
	_objectNode(nullptr), _id(0)
{
}

fenomen::render::RenderObject::~RenderObject()
{
}

void fenomen::render::RenderObject::initNode()
{
	RenderEngine& re = RenderEngine::Instance();

	_objectNode = re.createSceneNode();
	_id = _objectNode->getId();

	RenderEngine::Instance().addNodeToScene(_objectNode);
}

void fenomen::render::RenderObject::attachToNode()
{
	_objectNode->attachObject(_object);
}

void fenomen::render::RenderObject::destroy() {
	_object->detachFromParent();
	delete _object;

	RenderEngine::Instance().destroySceneNode(_objectNode);
}

void fenomen::render::RenderObject::setPos(const Vector& pos)
{
	_objectNode->setPosition(pos.x, pos.y, pos.z);
}

void fenomen::render::RenderObject::setRot(const Quaternion& rot)
{
	_objectNode->setOrientation(rot.w, rot.x, rot.y, rot.z);
}

void fenomen::render::RenderObject::setScale(const Vector& scale)
{
	_objectNode->setScale(scale.x, scale.y, scale.z);
}

void fenomen::render::RenderObject::setVisible(bool b)
{
	if(_objectNode)
		_objectNode->setVisible(b);
}

void fenomen::render::RenderObject::setStatic()
{
	if (_objectNode)
		_objectNode->setStatic(true);
}

void fenomen::render::RenderObject::setDynamic()
{
	if (_objectNode)
		_objectNode->setStatic(false);
}
