#pragma once

#include "Utils/vector.h"
#include "Components/component.h"
#include <memory>
#include <string>

namespace fenomen::sound {
	class Source3D;
}

namespace fenomen::logic {

class SourceComponent : public Component {
public:
	SourceComponent(Entity* owner);
	virtual ~SourceComponent();

	void Init();
	void Sync();

	void Create(const std::string& filePath, bool loop = false);

	void Play();
	void Stop();

	void Pause();
	void Resume();

	void SetLoop(bool b);

	void Set3DMinMaxDistance(double minDist, double maxDist);

protected:

	std::string filepath;
	bool bPlay, bLoop;
	std::unique_ptr<sound::Source3D> source;
};

}
