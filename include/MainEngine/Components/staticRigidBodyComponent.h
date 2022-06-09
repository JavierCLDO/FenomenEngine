#pragma once

#include "Utils/vector.h"
#include "Components/component.h"
#include <memory>
#include <string>

namespace fenomen::physics {
	class StaticRigidbody;
}

namespace fenomen::logic {

class StaticRigidBodyComponent : public Component {

public:
	StaticRigidBodyComponent(Entity* owner);
	virtual ~StaticRigidBodyComponent();

	virtual void Init() override;

	//Plane is infinite
	void CreatePlane();

	void Create(const Vector& halfSize = Vector::one, const Vector& offset = Vector::zero);

	void Create(double radius, const Vector& offset = Vector::zero);

	void SetStaticFriction(double fr);
	void SetDynamicFriction(double fr);
	void SetRestitution(double r);

	void EnableTrigger();
	void SetQueries(bool b);
	void EnableCollider();
	void SetCollisions(bool b);

protected:

	std::unique_ptr<physics::StaticRigidbody> rb;
};

}
