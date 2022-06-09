#pragma once

#include "Utils/vector.h"
#include "Components/component.h"
#include <memory>
#include <string>

namespace fenomen::physics {
	class DynamicRigidbody;
}

namespace fenomen::logic {

class DynamicRigidBodyComponent : public Component {

public:
	DynamicRigidBodyComponent(Entity* owner);
	virtual ~DynamicRigidBodyComponent();

	virtual void Init() override;

	void Sync() override;

	void Create(const Vector& halfSize = Vector::one, const Vector& offset = Vector::zero);
	void Create(double radius, const Vector& offset = Vector::zero);

	void SetStaticFriction(double fr);
	void SetDynamicFriction(double fr);
	void SetRestitution(double r);

	void EnableTrigger();
	void SetQueries(bool b);
	void SetCollisions(bool b);
	void EnableCollider();

protected:

	std::unique_ptr<physics::DynamicRigidbody> rb;
};

}
