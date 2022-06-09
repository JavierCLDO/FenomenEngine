#pragma once

class Vector {
public:
	union {
		struct {
			double x;
			double y;
			double z;
			double w;
		};
		double v[4];
	};
public:
	Vector(double X = 0.0, double Y = 0.0, double Z = 0.0);
	Vector(const Vector& v);
	~Vector();
	Vector& operator=(const Vector& v);

	Vector Normalized();
	void Normalize();
	double Magnitude();
	double SqrMagnitude();
	Vector Cross(Vector& other);
	double Dot(Vector& other);
	double Angle(Vector& other);

	static Vector Lerp(Vector& from, Vector& to, double t);
	static Vector Slerp(Vector& from, Vector& to, double t);
	static double Distance(Vector& v1, Vector& v2);
	static double SqrDistance(Vector& v1, Vector& v2);
	static void OrthoNormalize(Vector* normal, Vector* tangent);
	static void OrthoNormalize(Vector* normal, Vector* tangent, Vector* binormal);
	static Vector Project(Vector& vector, Vector& onNormal);
	static Vector Cross(Vector& lhs, Vector& rhs);
	static double Dot(Vector& lhs, Vector& rhs);
	static double Angle(Vector& lhs, Vector& rhs);
	static Vector Min(Vector& lhs, Vector& rhs);
	static Vector Max(Vector& lhs, Vector& rhs);

	Vector& operator+=(Vector& rhs);
	Vector& operator-=(Vector& rhs);
	Vector& operator*=(Vector& rhs);
	Vector& operator*=(double rhs);
	Vector operator+(Vector& rhs);
	Vector operator-(Vector& rhs);
	Vector operator*(Vector& rhs);
	Vector operator*(double rhs);
	bool operator==(Vector& rhs);
	bool operator!=(Vector& rhs);

	Vector& operator+=(const Vector& rhs);
	Vector& operator-=(const Vector& rhs);
	Vector& operator*=(const Vector& rhs);
	const Vector operator+(const Vector& rhs);
	Vector operator+(const Vector& rhs) const;
	const Vector operator-(const Vector& rhs);
	const Vector operator*(const Vector& rhs);
	bool operator==(const Vector& rhs);
	bool operator!=(const Vector& rhs);

	static const Vector zero;
	static const Vector one;
	static const Vector forward;
	static const Vector up;
	static const Vector right;
};

bool operator==(const Vector& lhs, const Vector& rhs);
bool operator!=(const Vector& lhs, const Vector& rhs);
const Vector operator*(double lhs, const Vector& rhs);
Vector operator*(double lhs, Vector& rhs);

