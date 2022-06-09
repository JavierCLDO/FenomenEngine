#pragma once
#include "vector.h"

namespace FMOD {
	class Channel;
	class Sound;
}

namespace fenomen::sound {

class Source3D {

public:

	Source3D();
	~Source3D();

	void create(const std::string& filename, bool loop = false);

	void play();
	void stop();

	void pause();
	void resume();

	void setLoop(bool b);

	void set3DMinMaxDistance(double minDist, double maxDist);

	void update(const Vector& pos, const Vector& vel);

private:

	FMOD::Channel* _channel;
	FMOD::Sound* _sound;
};

}