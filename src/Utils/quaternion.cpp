#include "pch.h"
#include "Quaternion.h"
#include <cmath>

// http://content.gpwiki.org/index.php/OpenGL:Tutorials:Using_Quaternions_to_represent_rotation
// http://www.flipcode.com/documents/matrfaq.html
// http://db-in.com/blog/2011/04/cameras-on-opengl-es-2-x/
// http://wiki.beyondunreal.com/Legacy:Quaternion
// http://clb.demon.fi/MathGeoLib/docs/double3x3.cpp_code.html#612
// http://clb.demon.fi/MathGeoLib/docs/Quat_summary.php
// http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
// http://www.koders.com/cpp/fid6E231B19C37F95D54405AEADD2C7CE1E84C5CEF1.aspx
// http://forums.create.msdn.com/forums/t/4574.aspx

const Quaternion Quaternion::identity(1.0, 0.0, 0.0, 0.0);

Quaternion::Quaternion() : w(1.0), x(0.0), y(0.0), z(0.0) { }
Quaternion::Quaternion(double W, double X, double Y, double Z) : w(W), x(X), y(Y), z(Z) { }
Quaternion::~Quaternion() { }

Quaternion::Quaternion(const Quaternion& q) {
	w = q.w;
	x = q.x;
	y = q.y;
	z = q.z;
}

Quaternion& Quaternion::operator=(const Quaternion& q) {
	if (this == &q) return *this;
	w = q.w;
	x = q.x;
	y = q.y;
	z = q.z;
	return *this;
}

Matrix Quaternion::ToMatrix(const Quaternion& q) {
	double sqw = q.w*q.w;
    double sqx = q.x*q.x;
    double sqy = q.y*q.y;
    double sqz = q.z*q.z;
    double invs = 1.0 / (sqx + sqy + sqz + sqw);

	Matrix matrix = Matrix::identity;

	matrix.mat[0] = ( sqx - sqy - sqz + sqw) * invs;
    matrix.mat[5] = (-sqx + sqy - sqz + sqw) * invs;
    matrix.mat[10] = (-sqx - sqy + sqz + sqw) * invs;
    
    double tmp1 = q.x*q.y;
    double tmp2 = q.z*q.w;
    matrix.mat[4] = 2.0 * (tmp1 + tmp2) * invs;
    matrix.mat[1] = 2.0 * (tmp1 - tmp2) * invs;
    
    tmp1 = q.x*q.z;
    tmp2 = q.y*q.w;
    matrix.mat[8] = 2.0 * (tmp1 - tmp2) * invs;
    matrix.mat[2] = 2.0 * (tmp1 + tmp2) * invs;

    tmp1 = q.y*q.z;
    tmp2 = q.x*q.w;
    matrix.mat[9] = 2.0 * (tmp1 + tmp2) * invs;
    matrix.mat[6] = 2.0 * (tmp1 - tmp2) * invs; 

	return matrix;
}

bool Quaternion::operator==(Quaternion& rhs) {
	return (w == rhs.w && x == rhs.x && y == rhs.y && z == rhs.z);
}

bool Quaternion::operator!=(Quaternion& rhs) {
	return !(w == rhs.w && x == rhs.x && y == rhs.y && z == rhs.z);
}

Quaternion& Quaternion::operator*=(Quaternion& rhs) {
	Quaternion q;
	
	q.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
	q.x = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
	q.y = w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x;
	q.z = w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w;

	*this = q;
	return *this;
}

Quaternion& Quaternion::operator*=(const Quaternion& rhs) {
	Quaternion q;
	
	q.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
	q.x = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
	q.y = w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x;
	q.z = w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w;

	*this = q;
	return *this;
}

Quaternion Quaternion::operator*(Quaternion& rhs) {
	Quaternion q;

	q.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
	q.x = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
	q.y = w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x;
	q.z = w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w;

	return q;
}

const Quaternion Quaternion::operator*(const Quaternion& rhs) {
	Quaternion q;

	q.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
	q.x = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
	q.y = w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x;
	q.z = w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w;

	return q;
}

Quaternion Quaternion::Normalized() {
	double mag = sqrtf(w * w + x * x + y * y + z * z);
	return Quaternion(w / mag, x / mag, y / mag, z / mag);
}

Quaternion Quaternion::Conjugate() {
	return Quaternion(w, -x, -y, -z);
}

void Quaternion::Normalize() {
	double mag = sqrtf(w * w + x * x + y * y + z * z);

	w /= mag;
	x /= mag;
	y /= mag;
	z /= mag;
}

Vector Quaternion::operator*(Vector& rhs) {
	return Quaternion::ToMatrix(*this) * rhs;
}

const Vector operator*(Vector& v, const Quaternion& m) {
	return Quaternion::ToMatrix(m) * v;
}

Vector operator*(Vector& v, Quaternion& m) {
	return Quaternion::ToMatrix(m) * v;
}

const Vector Quaternion::operator*(const Vector& rhs) {
	return Quaternion::ToMatrix(*this) * rhs;
}

Quaternion Quaternion::AngleAxis(double angle, Vector& axis) {
	Vector vn = axis.Normalized();

	angle *=  0.0174532925; // To radians!
	angle *= 0.5;	
	double sinAngle = sin(angle);
	
	return Quaternion(cos(angle), vn.x * sinAngle, vn.y * sinAngle, vn.z * sinAngle);
}

Quaternion Quaternion::Euler(double X, double Y, double Z) {
	X *= 0.0174532925; // To radians!
	Y *= 0.0174532925; // To radians!
	Z *= 0.0174532925; // To radians!

	X *= 0.5;
	Y *= 0.5;
	Z *= 0.5;

	double sinx = sinf(X);
	double siny = sinf(Y);
	double sinz = sinf(Z);
	double cosx = cosf(X);
	double cosy = cosf(Y);
	double cosz = cosf(Z);

	Quaternion q;

	q.w = cosx * cosy * cosz + sinx * siny * sinz;
	q.x = sinx * cosy * cosz + cosx * siny * sinz;
	q.y = cosx * siny * cosz - sinx * cosy * sinz;
	q.z = cosx * cosy * sinz - sinx * siny * cosz;

	return q;
}

void Quaternion::SetEuler(double X, double Y, double Z) {
	X *= 0.0174532925; // To radians!
	Y *= 0.0174532925; // To radians!
	Z *= 0.0174532925; // To radians!

	X *= 0.5;
	Y *= 0.5;
	Z *= 0.5;

	double sinx = sinf(X);
	double siny = sinf(Y);
	double sinz = sinf(Z);
	double cosx = cosf(X);
	double cosy = cosf(Y);
	double cosz = cosf(Z);

	w = cosx * cosy * cosz + sinx * siny * sinz;
	x = sinx * cosy * cosz + cosx * siny * sinz;
	y = cosx * siny * cosz - sinx * cosy * sinz;
	z = cosx * cosy * sinz - sinx * siny * cosz;
}

void Quaternion::ToAngleAxis(double* angle, Vector* axis) {
	*angle = acosf(w);
	double sinz = sinf(*angle);

	if (fabsf(sinz) > 1e-4f) {
		sinz = 1.0 / sinz;

		axis->x = x * sinz;
		axis->y = y * sinz;
		axis->z = z * sinz;
		
		*angle *= 2.0 * 57.2957795;
		if (*angle > 180.0)
			*angle = 360.0 - *angle;
	} else {
		*angle = 0.0;
		axis->x = 1.0;
		axis->y = 0.0;
		axis->z = 0.0;
	}
}

Quaternion Quaternion::Inverse(Quaternion& rotation) {
	return Quaternion(rotation.w, -1.0 * rotation.x, -1.0 * rotation.y, -1.0 * rotation.z);
}

double Quaternion::Dot(Quaternion& a, Quaternion& b) {
	return (a.w * b.w + a.x * b.x * a.y * b.y + a.z * b.z);
}

double Quaternion::Dot(Quaternion& b) {
	return (w * b.w + x * b.x * y * b.y + z * b.z);
}

double Quaternion::Angle(Quaternion& a, Quaternion& b) {
	double degrees = acosf((b * Quaternion::Inverse(a)).w) * 2.0 * 57.2957795;
	if (degrees > 180.0)
		return 360.0 - degrees;
	return degrees;
}

Quaternion operator*(double f, Quaternion& m) {
	return Quaternion(m.w * f, m.x * f, m.y * f, m.z * f);
}

const Quaternion operator*(double f, const Quaternion& m) {
	return Quaternion(m.w * f, m.x * f, m.y * f, m.z * f);
}

Quaternion Quaternion::operator*(double& f) {
	return Quaternion(w * f, x * f, y * f, z * f);
}

const Quaternion Quaternion::operator*(const double& f) {
	return Quaternion(w * f, x * f, y * f, z * f);
}

Quaternion Quaternion::operator+(Quaternion& rhs) {
	return Quaternion(w + rhs.w, x + rhs.x, y + rhs.y, z + rhs.z);
}

const Quaternion Quaternion::operator+(const Quaternion& rhs) {
	return Quaternion(w + rhs.w, x + rhs.x, y + rhs.y, z + rhs.z);
}

Quaternion Quaternion::Lerp(Quaternion& from, Quaternion& to, double t) {
	Quaternion src = from * (1.0 - t);
	Quaternion dst = to * t;

	Quaternion q = src + dst;
	return q;
}

Quaternion Quaternion::Slerp(Quaternion& from, Quaternion& to, double t) {
	double cosTheta = Quaternion::Dot(from, to);
	Quaternion temp(to);

	if (cosTheta < 0.0) {
		cosTheta *= -1.0;
		temp = temp * -1.0;
	}

	double theta = acosf(cosTheta);
	double sinTheta = 1.0 / sinf(theta);

	return sinTheta * (
		((Quaternion)(from * sinf(theta * (1.0 - t)))) + 
		((Quaternion)(temp * sinf(t * theta)))
		);
}

#define m00 right.x
#define m01 up.x
#define m02 forward.x
#define m10 right.y
#define m11 up.y
#define m12 forward.y
#define m20 right.z
#define m21 up.z
#define m22 forward.z

Quaternion Quaternion::LookRotation(Vector& lookAt, Vector& upDirection) {
	Vector forward = lookAt; Vector up = upDirection;
	Vector::OrthoNormalize(&forward, &up);
	Vector right = Vector::Cross(up, forward);

	Quaternion ret;
	ret.w = sqrtf(1.0 + m00 + m11 + m22) * 0.5;
	double w4_recip = 1.0 / (4.0 * ret.w);
	ret.x = (m21 - m12) * w4_recip;
	ret.y = (m02 - m20) * w4_recip;
	ret.z = (m10 - m01) * w4_recip;

	return ret;
}

Quaternion Quaternion::LookRotation(Vector& lookAt) {
	Vector up = (Vector)Vector::up;
	Vector forward = lookAt;
	Vector::OrthoNormalize(&forward, &up);
	Vector right = Vector::Cross(up, forward);

	Quaternion ret;
	ret.w = sqrtf(1.0 + m00 + m11 + m22) * 0.5;
	double w4_recip = 1.0 / (4.0 * ret.w);
	ret.x = (m21 - m12) * w4_recip;
	ret.y = (m02 - m20) * w4_recip;
	ret.z = (m10 - m01) * w4_recip;

	return ret;
}

void Quaternion::SetLookRotation(Vector& lookAt) {
	Vector up = (Vector)Vector::up;
	Vector forward = lookAt;
	Vector::OrthoNormalize(&forward, &up);
	Vector right = Vector::Cross(up, forward);

	w = sqrtf(1.0 + m00 + m11 + m22) * 0.5;
	double w4_recip = 1.0 / (4.0 * w);
	x = (m21 - m12) * w4_recip;
	y = (m02 - m20) * w4_recip;
	z = (m10 - m01) * w4_recip;
}

void Quaternion::SetLookRotation(Vector& lookAt, Vector& upDirection) {
	Vector forward = lookAt; Vector up = upDirection;
	Vector::OrthoNormalize(&forward, &up);
	Vector right = Vector::Cross(up, forward);

	w = sqrtf(1.0 + m00 + m11 + m22) * 0.5;
	double w4_recip = 1.0 / (4.0 * w);
	x = (m21 - m12) * w4_recip;
	y = (m02 - m20) * w4_recip;
	z = (m10 - m01) * w4_recip;
}

#undef m00
#undef m01
#undef m02
#undef m10
#undef m11
#undef m12
#undef m20
#undef m21
#undef m22
