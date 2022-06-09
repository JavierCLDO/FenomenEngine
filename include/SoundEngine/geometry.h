#pragma once
#include "vector.h"
#include <list>
#include <vector>
#include <quaternion.h>

namespace FMOD {
	class Geometry;
}

namespace fenomen::sound {

class Geometry {
private:
	struct Polygon {
		float directocclusion;
		float reverbocclusion;
		bool doublesided;
		int numvertices;
		std::vector<Vector> vertices;
	};
public:

	Geometry();
	~Geometry();

	void setEnable(bool b);

	void create(int maxpolygons, int maxvertices);
	void addPlane(float directocclusion, float reverbocclusion, bool doublesided, const std::vector<Vector>& vertices);

	void setPos(const Vector& pos);
	void setRot(const Vector& forward, const Vector& up);
	void setScale(const Vector& scale);

private:

	std::list<int> polygonsIndex;
	std::list<Polygon> polygons;

	FMOD::Geometry* _geometry;
};

}