#pragma once

#include <string>

namespace Ogre {
	class SceneNode;
	class MovableObject;
}

class Vector;
class Quaternion;

namespace fenomen::render {

class RenderObject {

public:

	virtual ~RenderObject();

	virtual void destroy();
	void initNode();
	void attachToNode();

	void setPos(const Vector& pos);
	void setRot(const Quaternion& rot);
	void setScale(const Vector& scale);

	void setVisible(bool b);
	void setStatic();
	void setDynamic();

	virtual void create(const std::string&) = 0;

protected:

	RenderObject();
	Ogre::SceneNode* _objectNode;
	Ogre::MovableObject* _object;

	uint32_t _id;

public:
	inline const uint32_t& getID() const { return _id; }
};

}