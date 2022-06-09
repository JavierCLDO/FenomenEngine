#pragma once
#include <string>
#include "renderObject.h"

namespace Ogre {
	class Light;
}

namespace fenomen::render {

class LightObject : public RenderObject{

public:

	virtual ~LightObject();

	virtual void create(const std::string& name = "");

protected:
	LightObject();

	Ogre::Light* _objectLight;

public:

    void setPower(double power);
	double getPower() const;

	void setDiffuse(double r, double g, double b);
    void setSpecular(double r, double g, double b);
    void setCastShadows(bool b);
};

}