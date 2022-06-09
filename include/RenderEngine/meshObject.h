#pragma once
#include <string>
#include "renderObject.h"
#include "vector.h"

namespace Ogre {
	class Item;
}

namespace fenomen::render {

class MeshObject : public RenderObject{

public:

	MeshObject();
	virtual ~MeshObject();

	void create(const std::string& mesh);

	void createPlane(double width = 2.0, double height = 2.0, uint32_t xsegments = 1, uint32_t ysegments = 1, double utile = 1.0, double vtile = 1.0);

	void setDatablock(const std::string& name);

	const Vector& getAABB() { return _meshSize; }
	const Vector& getHalfAABB() { return _meshSize * 0.5; }

protected:
	Ogre::Item* _objectItem;

private:
	std::string _meshName;
	Vector _meshSize;
};

}