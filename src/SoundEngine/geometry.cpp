#include "pch.h"
#include "geometry.h"
#include "soundEngine.h"
#include "fmod.hpp"

fenomen::sound::Geometry::Geometry() : _geometry(nullptr), polygons(), polygonsIndex()
{
}

fenomen::sound::Geometry::~Geometry()
{
}

void fenomen::sound::Geometry::setEnable(bool b)
{
	if (!_geometry)
		return;

	_geometry->setActive(b);
}

void fenomen::sound::Geometry::create(int maxpolygons, int maxvertices)
{
	auto sys = SoundEngine::Instance().getSystem();

	sys->createGeometry(maxpolygons, maxvertices, &_geometry);

	for (auto& polygon : polygons) {

		std::vector<FMOD_VECTOR> vertex;

		vertex.reserve(polygon.numvertices);
		for (int i = 0; i < polygon.numvertices; i++)
		{
			FMOD_VECTOR aux{ polygon.vertices[i].x, polygon.vertices[i].y, polygon.vertices[i].z };
			vertex.emplace_back(aux);
		}

		polygonsIndex.push_back(0);
		_geometry->addPolygon(polygon.directocclusion, polygon.reverbocclusion, polygon.doublesided, polygon.numvertices, vertex.data(), &polygonsIndex.back());
	}
}

void fenomen::sound::Geometry::addPlane(float directocclusion, float reverbocclusion, bool doublesided, const std::vector<Vector>& vertices)
{
	Polygon p{ directocclusion, reverbocclusion, doublesided, vertices.size(), vertices };
	polygons.push_back(p);
}

void fenomen::sound::Geometry::setPos(const Vector& pos)
{
	if (!_geometry)
		return;

	FMOD_VECTOR aux{ pos.x, pos.y, pos.z };

	_geometry->setPosition(&aux);
}

void fenomen::sound::Geometry::setRot(const Vector& forward, const Vector& up)
{
	if (!_geometry)
		return;

	FMOD_VECTOR f{ forward.x, forward.y, forward.z };
	FMOD_VECTOR u{ up.x, up.y, up.z };

	_geometry->setRotation(&f, &u);
}

void fenomen::sound::Geometry::setScale(const Vector& scale)
{
	if (!_geometry)
		return;

	FMOD_VECTOR aux{ scale.x, scale.y, scale.z };

	_geometry->setScale(&aux);
}
