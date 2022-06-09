#pragma once

#include "Utils/vector.h"
#include "Components/component.h"
#include <memory>
#include <string>

namespace fenomen::sound {
	class Geometry;
}

namespace fenomen::logic {

class AudioGeometryComponent : public Component {

public:
	typedef enum {
		Plane, 
		Cube
	} Preset;

public:
	AudioGeometryComponent(Entity* owner);
	virtual ~AudioGeometryComponent();

	void Init();

	void Update(double deltaTime);

	void Create(Preset preset, float directocclusion, float reverbocclusion, const Vector& halfSize = Vector::one, bool doublesided = false);

protected:

	void _createPlane(float directocclusion, float reverbocclusion, const Vector& halfSize, bool doublesided);
	void _createCube(float directocclusion, float reverbocclusion, const Vector& halfSize, bool doublesided);

	std::unique_ptr<sound::Geometry> geometry;
};

}
