#pragma once

#include "vector.h"
#include "matrix.h"

class Quaternion {
public:
	double w, x, y, z;
public:
	Quaternion();
	Quaternion(double W, double X, double Y, double Z);
	Quaternion(const Quaternion& q);
	~Quaternion();
	Quaternion& operator=(const Quaternion&);

	bool operator==(Quaternion& rhs);
	bool operator!=(Quaternion& rhs);

	Quaternion& operator*=(Quaternion& rhs);
	Quaternion& operator*=(const Quaternion& rhs);
	Quaternion operator*(Quaternion& rhs);
	const Quaternion operator*(const Quaternion& rhs);
	Quaternion operator*(double& rhs);
	const Quaternion operator*(const double& rhs);
	Quaternion operator+(Quaternion& rhs);
	const Quaternion operator+(const Quaternion& rhs);
	Vector operator*(Vector& rhs);
	const Vector operator*(const Vector& rhs);

	Quaternion Normalized();
	void Normalize();
	Quaternion Conjugate(); // Same as inverse

	void ToAngleAxis(double* angle, Vector* axis);
	void SetEuler(double X, double Y, double Z);
	double Dot(Quaternion& b);
	void SetLookRotation(Vector& lookAt);
	void SetLookRotation(Vector& lookAt, Vector& upDirection);

	static Quaternion LookRotation(Vector& lookAt);
	static Quaternion LookRotation(Vector& lookAt, Vector& upDirection);
	static Quaternion Slerp(Quaternion& from, Quaternion& to, double t);
	static Quaternion Lerp(Quaternion& from, Quaternion& to, double t);
	static double Angle(Quaternion& a, Quaternion& b);
	static double Dot(Quaternion& a, Quaternion& b);
	static Quaternion AngleAxis(double angle, Vector& axis);
	static Quaternion Inverse(Quaternion& rotation);
	static Quaternion Euler(double X, double Y, double Z);
	static Matrix ToMatrix(const Quaternion& q);

	static const Quaternion identity;
};

const Vector operator*(Vector& v, const Quaternion& m);
Vector operator*(Vector& v, Quaternion& m);
Quaternion operator*(double f, Quaternion& m);
const Quaternion operator*(double f, const Quaternion& m);


