#pragma once
#include <memory>

namespace FMOD {
	class System;
	class Sound;
}

namespace fenomen::sound {

class SoundEngine {

public:

	~SoundEngine();

	inline static SoundEngine& Instance() { return *instance; }

	static SoundEngine& CreateInstance();

	int Init(const std::string& path);
	void Update();
	int Close();

	FMOD::Sound* createSound(const std::string& fileName);

	inline FMOD::System* getSystem() { return _system; }

private:

	static std::unique_ptr<SoundEngine> instance;

	SoundEngine();

	std::string _path;
	FMOD::System* _system;
};

}