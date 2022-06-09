#pragma once

#include "Utils/vector.h"
#include "Utils/quaternion.h"
#include "Components/component.h"

namespace fenomen::logic {

class Transform : public Component {
public:
	Transform(Entity* owner);
	~Transform();

	void Init() override;
	void Update(double deltaTime) override;

	void Translate(const Vector& movement);

	void MoveForward(double value);
	void MoveRight(double value);
	void MoveUp(double value);

	void MoveForwardGlobal(double value);
	void MoveRightGlobal(double value);
	void MoveUpGlobal(double value);

	void Yaw(double angle, bool local = true);
	void Roll(double angle, bool local = true);
	void Pitch(double angle, bool local = true);

	void LookAt(const Vector& target);

	inline void LockPitchAt90(bool b) { bLockPitch = b; }

protected:
	Vector pos;
	Vector vel;
	Vector scale;
	Quaternion rot;

	double totalPitch;
	bool bLockPitch;

private:

	void _updateDirs();

	Vector forward;
	Vector right;
	Vector up;
	Vector lastPos;

public:
	void setPos(const Vector& newPos);
	inline const Vector& getPos() { return pos; }
	inline Vector& getPosRef() { return pos; }

	void setRot(const Quaternion& newRot);
	inline const Quaternion& getRot() { return rot; }
	inline Quaternion& getRotRef() { return rot; }

	void setScale(const Vector& newScale);
	inline const Vector& getScale() { return scale; }

	inline const Vector& getVel() { return vel; }
	inline const Vector& getForward() { return forward; }
	inline const Vector& getRight() { return right; }
	inline const Vector& getUp() { return up; }
};

}
