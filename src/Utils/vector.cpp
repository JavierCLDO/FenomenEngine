#include "pch.h"
#include "Vector.h"
#include <cmath>

const Vector Vector::zero(0.0, 0.0, 0.0);
const Vector Vector::one(1.0, 1.0, 1.0);
const Vector Vector::forward(0.0, 0.0, -1.0);
const Vector Vector::up(0.0, 1.0, 0.0);
const Vector Vector::right(1.0, 0.0, 0.0);

Vector::Vector(double X, double Y, double Z) : x(X), y(Y), z(Z), w(0.0) {}

Vector::Vector(const Vector& v) {
	x = v.x;
	y = v.y;
	z = v.z;
	w = 0.0f;
}

Vector::~Vector() {}

Vector& Vector::operator=(const Vector& v) {
	if (this == &v) return *this;
	x = v.x;
	y = v.y;
	z = v.z;
	w = 0.0f;
	return *this;
}

Vector Vector::Normalized() {
	double len = sqrtf(x * x + y * y + z * z);
	return Vector(x / len, y / len, z / len);
}

void Vector::Normalize() {
	double len = sqrtf(x * x + y * y + z * z);
	x /= len;
	y /= len;
	z /= len;
}

double Vector::Magnitude() {
	return sqrtf(x * x + y * y + z * z);
}

double Vector::SqrMagnitude() {
	return (x * x + y * y + z * z);
}

Vector Vector::Cross(Vector& other) {
	double X = y * other.z - z * other.y;
	double Y = z * other.x - x * other.z;
	double Z = x * other.y - y * other.x;
	return Vector(X, Y, Z);
}

double Vector::Dot(Vector& other) {
	return (x * other.x + y * other.y + z * other.z);
}

double Vector::Angle(Vector& other) { // Angle in degrees
	return atan2f(Vector::Cross(*this, other).Magnitude() * -1.0f, Vector::Dot(*this, other) * -1.0f) / 3.14f * 180.0f + 180.0f;
}

Vector Vector::Lerp(Vector& from, Vector& to, double t) {
	return from + ((Vector)(to - from) * t);
}

Vector Vector::Slerp(Vector& from, Vector& to, double t) {
	double dot = Vector::Dot(from, to);

	if (dot < -1.0f) dot = -1.0f;
	if (dot > 1.0f) dot = 1.0f;

	double theta = acosf(dot) * t;
	Vector relative = (to - (from * dot));
	relative.Normalize();

	return ((Vector)(from * cosf(theta)) + (Vector)(relative * sinf(theta)));
}

void Vector::OrthoNormalize(Vector* normal, Vector* tangent) {
	normal->Normalize();
	Vector norm = *normal;
	Vector tan = tangent->Normalized();

	*tangent = tan - (norm * Vector::Dot(norm, tan));
	tangent->Normalize();
}

void Vector::OrthoNormalize(Vector* normal, Vector* tangent, Vector* binormal) {
	Vector norm, tan, binorm;

	normal->Normalize();
	norm = *normal;
	tan = tangent->Normalized();

	Vector temp = Vector::Cross(norm, tan);
	*tangent = Vector::Cross(temp, norm);
	tangent->Normalize();

	*binormal = Vector::Cross(norm, *tangent);
	binormal->Normalize();
}

Vector Vector::Project(Vector& vector, Vector& onNormal) {
	Vector theNormal = onNormal.Normalized();
	return theNormal * Vector::Dot(vector, theNormal);
}

Vector Vector::Cross(Vector& lhs, Vector& rhs) {
	double X = lhs.y * rhs.z - lhs.z * rhs.y;
	double Y = lhs.z * rhs.x - lhs.x * rhs.z;
	double Z = lhs.x * rhs.y - lhs.y * rhs.x;
	return Vector(X, Y, Z);
}

double Vector::Dot(Vector& lhs, Vector& rhs) {
	return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
}

double Vector::Distance(Vector& v1, Vector& v2) {
	Vector r = v2 - v1;
	return sqrtf(r.x * r.x + r.y * r.y + r.z * r.z);
}

double Vector::SqrDistance(Vector& v1, Vector& v2) {
	Vector r = v2 - v1;
	return (r.x * r.x + r.y * r.y + r.z * r.z);
}


double Vector::Angle(Vector& lhs, Vector& rhs) {
	return lhs.Angle(rhs);
}

Vector Vector::Min(Vector& lhs, Vector& rhs) {
	double X = (lhs.x < rhs.x) ? lhs.x : rhs.x;
	double Y = (lhs.y < rhs.y) ? lhs.y : rhs.y;
	double Z = (lhs.z < rhs.z) ? lhs.z : rhs.z;
	return Vector(X, Y, Z);
}

Vector Vector::Max(Vector& lhs, Vector& rhs) {
	double X = (lhs.x < rhs.x) ? rhs.x : lhs.x;
	double Y = (lhs.y < rhs.y) ? rhs.y : lhs.y;
	double Z = (lhs.z < rhs.z) ? rhs.z : lhs.z;
	return Vector(X, Y, Z);
}

Vector& Vector::operator+=(Vector& rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vector& Vector::operator-=(Vector& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vector& Vector::operator*=(Vector& rhs) {
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}

Vector& Vector::operator*=(double rhs) {
	x *= rhs;
	y *= rhs;
	z *= rhs;
	return *this;
}

Vector Vector::operator+(Vector& rhs) {
	return Vector(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vector Vector::operator-(Vector& rhs) {
	return Vector(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vector Vector::operator*(Vector& rhs) {
	return Vector(x * rhs.x, y * rhs.y, z * rhs.z);
}

Vector Vector::operator*(double rhs) {
	return Vector(x * rhs, y * rhs, z * rhs);
}

bool Vector::operator==(Vector& rhs) {
	return (x == rhs.x && y == rhs.y && z == rhs.z);
}

bool Vector::operator!=(Vector& rhs) {
	return !(x == rhs.x && y == rhs.y && z == rhs.z);
}

Vector& Vector::operator+=(const Vector& rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vector& Vector::operator-=(const Vector& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vector& Vector::operator*=(const Vector& rhs) {
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}

const Vector Vector::operator+(const Vector& rhs) {
	return Vector(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vector Vector::operator+(const Vector& rhs) const
{
	return Vector(x + rhs.x, y + rhs.y, z + rhs.z);
}

const Vector Vector::operator-(const Vector& rhs) {
	return Vector(x - rhs.x, y - rhs.y, z - rhs.z);
}

const Vector Vector::operator*(const Vector& rhs) {
	return Vector(x * rhs.x, y * rhs.y, z * rhs.z);
}

bool Vector::operator==(const Vector& rhs) {
	return (x == rhs.x && y == rhs.y && z == rhs.z);
}

bool Vector::operator!=(const Vector& rhs) {
	return !(x == rhs.x && y == rhs.y && z == rhs.z);
}

bool operator==(const Vector& lhs, const Vector& rhs) {
	return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z);
}

bool operator!=(const Vector& lhs, const Vector& rhs) {
	return !(lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z);
}

const Vector operator*(double lhs, const Vector& rhs) {
	return Vector(rhs.x * lhs, rhs.y * lhs, rhs.y * lhs);
}

Vector operator*(double lhs, Vector& rhs) {
	return Vector(rhs.x * lhs, rhs.y * lhs, rhs.y * lhs);
}