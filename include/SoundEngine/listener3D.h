#pragma once
#include "vector.h"

namespace fenomen::sound {

class Listener3D {

public:

	Listener3D();
	~Listener3D();

	void update(const Vector& pos, const Vector& vel, const Vector& forward, const Vector& up);

};

}