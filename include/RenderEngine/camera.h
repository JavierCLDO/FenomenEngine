#pragma once
#include <string>
#include "renderObject.h"

namespace Ogre {
	class Camera;
}

namespace fenomen::render {

class Camera : public RenderObject {

public:

	Camera();
	virtual ~Camera();

	void destroy() override;
	void create(const std::string&);

protected:
	Ogre::Camera* _objectCamera;
};

}