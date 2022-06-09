#include "pch.h"
#include "Components/transform.h"
#include "entity.h"

fenomen::logic::Transform::Transform(Entity* owner): Component(owner), 
	pos(0.0, 0.0, 0.0), scale(1.0, 1.0, 1.0), rot(1.0, 0.0, 0.0, 0.0), bLockPitch(false), totalPitch(),
	lastPos(0.0, 0.0, 0.0), forward(Vector::forward), right(Vector::right), up(Vector::up)
{
	bTick = true;
}

fenomen::logic::Transform::~Transform()
{
}

void fenomen::logic::Transform::Init()
{
}

void fenomen::logic::Transform::Update(double deltaTime)
{
	rot.Normalize();

	vel = pos - lastPos;
	lastPos = pos;
}

void fenomen::logic::Transform::Translate(const Vector& movement)
{
	pos += movement;
}

void fenomen::logic::Transform::MoveForward(double value)
{
	pos += forward * value;
}

void fenomen::logic::Transform::MoveRight(double value)
{
	pos += right * value;
}

void fenomen::logic::Transform::MoveUp(double value)
{
	pos += up * value;
}

void fenomen::logic::Transform::MoveForwardGlobal(double value)
{
	Vector aux = forward;
	aux.y = 0;
	pos += aux * value;
}

void fenomen::logic::Transform::MoveRightGlobal(double value)
{
	Vector aux = right;
	aux.y = 0;
	pos += aux * value;
}

void fenomen::logic::Transform::MoveUpGlobal(double value)
{
	pos.y += value;
}

void fenomen::logic::Transform::Yaw(double angle, bool local)
{
	Vector x = Vector::up;
	Quaternion q = Quaternion::AngleAxis(angle, x);
	rot = local ? rot * q : q * rot;
	_updateDirs();
}

void fenomen::logic::Transform::Roll(double angle, bool local)
{
	Vector x = Vector::forward;
	Quaternion q = Quaternion::AngleAxis(angle, x);
	rot = local ? rot * q : q * rot;
	_updateDirs();
}

void fenomen::logic::Transform::Pitch(double angle, bool local)
{
	if (bLockPitch){
		double aux = totalPitch + angle;

		if (aux < -90.0 || aux > 90.0) {
			return;
		}

		totalPitch = aux;
	}

	Vector x = Vector::right;
	Quaternion q = Quaternion::AngleAxis(angle, x);
	rot = local ? rot * q : q * rot;
	_updateDirs();
}

void fenomen::logic::Transform::LookAt(const Vector& target)
{
	Vector dir = pos - target;
	rot.SetLookRotation(dir);
	_updateDirs();
}

void fenomen::logic::Transform::_updateDirs()
{
	forward = rot * Vector::forward;
	right = rot * Vector::right;
	up = rot * Vector::up;
}

void fenomen::logic::Transform::setPos(const Vector& newPos)
{
	pos = newPos;
	owner->PositionChanged();
}

void fenomen::logic::Transform::setRot(const Quaternion& newRot)
{
	rot = newRot;
	_updateDirs();
	owner->RotationChanged();
}

void fenomen::logic::Transform::setScale(const Vector& newScale)
{
	scale = newScale;
}
