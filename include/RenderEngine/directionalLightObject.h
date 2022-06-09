#pragma once
#include <string>
#include "lightObject.h"

namespace fenomen::render {

class DirectionalLightObject : public LightObject{

public:
    DirectionalLightObject();

	virtual ~DirectionalLightObject();

	void create(const std::string& name = "") override;

	void setAsSun();
};

}