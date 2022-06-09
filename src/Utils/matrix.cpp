#include "pch.h"
#include "matrix.h"
#include <string>
#include <cmath>

#define MATRIXELEMENT(mat, row, col) mat[row * 4 + col]

const Matrix Matrix::zero;
const Matrix Matrix::identity(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

Matrix::Matrix() {
	memset(mat, 0, sizeof(float) * 16);
}

Matrix::Matrix(float _0, float _1, float _2, float _3, float _4, float _5, float _6, float _7, float _8, float _9, float _10, float _11, float _12, float _13, float _14, float _15) {
	mat[0] = _0;
	mat[1] = _1;
	mat[2] = _2;
	mat[3] = _3;
	mat[4] = _4;
	mat[5] = _5;
	mat[6] = _6;
	mat[7] = _7;
	mat[8] = _8;
	mat[9] = _9;
	mat[10] = _10;
	mat[11] = _11;
	mat[12] = _12;
	mat[13] = _13;
	mat[14] = _14;
	mat[15] = _15;
}


Matrix::~Matrix() { }

Matrix::Matrix(const Matrix& m) {
	memcpy(mat, m.mat, sizeof(float) * 16);
}

Matrix& Matrix::operator=(const Matrix& m) {
	if (this == &m) return *this;
	memcpy(mat, m.mat, sizeof(float) * 16);
	return *this;
}


Matrix& Matrix::operator*=(Matrix& rhs) {
	Matrix newMatrix;

	newMatrix.mat[0] = mat[0] * rhs.mat[0] + mat[1] * rhs.mat[4] + mat[2] * rhs.mat[8] + mat[3] * rhs.mat[12];
	newMatrix.mat[1] = mat[0] * rhs.mat[1] + mat[1] * rhs.mat[5] + mat[2] * rhs.mat[9] + mat[3] * rhs.mat[13];
	newMatrix.mat[2] = mat[0] * rhs.mat[2] + mat[1] * rhs.mat[6] + mat[2] * rhs.mat[10] + mat[3] * rhs.mat[14];
	newMatrix.mat[3] = mat[0] * rhs.mat[3] + mat[1] * rhs.mat[7] + mat[2] * rhs.mat[11] + mat[3] * rhs.mat[15];
	newMatrix.mat[4] = mat[4] * rhs.mat[0] + mat[5] * rhs.mat[4] + mat[6] * rhs.mat[8] + mat[7] * rhs.mat[12];
	newMatrix.mat[5] = mat[4] * rhs.mat[1] + mat[5] * rhs.mat[5] + mat[6] * rhs.mat[9] + mat[7] * rhs.mat[13];
	newMatrix.mat[6] = mat[4] * rhs.mat[2] + mat[5] * rhs.mat[6] + mat[6] * rhs.mat[10] + mat[7] * rhs.mat[14];
	newMatrix.mat[7] = mat[4] * rhs.mat[3] + mat[5] * rhs.mat[7] + mat[6] * rhs.mat[11] + mat[7] * rhs.mat[15];
	newMatrix.mat[8] = mat[8] * rhs.mat[0] + mat[9] * rhs.mat[4] + mat[10] * rhs.mat[8] + mat[11] * rhs.mat[12];
	newMatrix.mat[9] = mat[8] * rhs.mat[1] + mat[9] * rhs.mat[5] + mat[10] * rhs.mat[9] + mat[11] * rhs.mat[13];
	newMatrix.mat[10] = mat[8] * rhs.mat[2] + mat[9] * rhs.mat[6] + mat[10] * rhs.mat[10] + mat[11] * rhs.mat[14];
	newMatrix.mat[11] = mat[8] * rhs.mat[3] + mat[9] * rhs.mat[7] + mat[10] * rhs.mat[11] + mat[11] * rhs.mat[15];
	newMatrix.mat[12] = mat[12] * rhs.mat[0] + mat[13] * rhs.mat[4] + mat[14] * rhs.mat[8] + mat[15] * rhs.mat[12];
	newMatrix.mat[13] = mat[12] * rhs.mat[1] + mat[13] * rhs.mat[5] + mat[14] * rhs.mat[9] + mat[15] * rhs.mat[13];
	newMatrix.mat[14] = mat[12] * rhs.mat[2] + mat[13] * rhs.mat[6] + mat[14] * rhs.mat[10] + mat[15] * rhs.mat[14];
	newMatrix.mat[15] = mat[12] * rhs.mat[3] + mat[13] * rhs.mat[7] + mat[14] * rhs.mat[11] + mat[15] * rhs.mat[15];

	*this = newMatrix;
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& rhs) {
	Matrix newMatrix;

	newMatrix.mat[0] = mat[0] * rhs.mat[0] + mat[1] * rhs.mat[4] + mat[2] * rhs.mat[8] + mat[3] * rhs.mat[12];
	newMatrix.mat[1] = mat[0] * rhs.mat[1] + mat[1] * rhs.mat[5] + mat[2] * rhs.mat[9] + mat[3] * rhs.mat[13];
	newMatrix.mat[2] = mat[0] * rhs.mat[2] + mat[1] * rhs.mat[6] + mat[2] * rhs.mat[10] + mat[3] * rhs.mat[14];
	newMatrix.mat[3] = mat[0] * rhs.mat[3] + mat[1] * rhs.mat[7] + mat[2] * rhs.mat[11] + mat[3] * rhs.mat[15];
	newMatrix.mat[4] = mat[4] * rhs.mat[0] + mat[5] * rhs.mat[4] + mat[6] * rhs.mat[8] + mat[7] * rhs.mat[12];
	newMatrix.mat[5] = mat[4] * rhs.mat[1] + mat[5] * rhs.mat[5] + mat[6] * rhs.mat[9] + mat[7] * rhs.mat[13];
	newMatrix.mat[6] = mat[4] * rhs.mat[2] + mat[5] * rhs.mat[6] + mat[6] * rhs.mat[10] + mat[7] * rhs.mat[14];
	newMatrix.mat[7] = mat[4] * rhs.mat[3] + mat[5] * rhs.mat[7] + mat[6] * rhs.mat[11] + mat[7] * rhs.mat[15];
	newMatrix.mat[8] = mat[8] * rhs.mat[0] + mat[9] * rhs.mat[4] + mat[10] * rhs.mat[8] + mat[11] * rhs.mat[12];
	newMatrix.mat[9] = mat[8] * rhs.mat[1] + mat[9] * rhs.mat[5] + mat[10] * rhs.mat[9] + mat[11] * rhs.mat[13];
	newMatrix.mat[10] = mat[8] * rhs.mat[2] + mat[9] * rhs.mat[6] + mat[10] * rhs.mat[10] + mat[11] * rhs.mat[14];
	newMatrix.mat[11] = mat[8] * rhs.mat[3] + mat[9] * rhs.mat[7] + mat[10] * rhs.mat[11] + mat[11] * rhs.mat[15];
	newMatrix.mat[12] = mat[12] * rhs.mat[0] + mat[13] * rhs.mat[4] + mat[14] * rhs.mat[8] + mat[15] * rhs.mat[12];
	newMatrix.mat[13] = mat[12] * rhs.mat[1] + mat[13] * rhs.mat[5] + mat[14] * rhs.mat[9] + mat[15] * rhs.mat[13];
	newMatrix.mat[14] = mat[12] * rhs.mat[2] + mat[13] * rhs.mat[6] + mat[14] * rhs.mat[10] + mat[15] * rhs.mat[14];
	newMatrix.mat[15] = mat[12] * rhs.mat[3] + mat[13] * rhs.mat[7] + mat[14] * rhs.mat[11] + mat[15] * rhs.mat[15];

	*this = newMatrix;
	return *this;
}

Matrix Matrix::operator*(Matrix& rhs) {
	Matrix newMatrix;

	newMatrix.mat[0] = mat[0] * rhs.mat[0] + mat[1] * rhs.mat[4] + mat[2] * rhs.mat[8] + mat[3] * rhs.mat[12];
	newMatrix.mat[1] = mat[0] * rhs.mat[1] + mat[1] * rhs.mat[5] + mat[2] * rhs.mat[9] + mat[3] * rhs.mat[13];
	newMatrix.mat[2] = mat[0] * rhs.mat[2] + mat[1] * rhs.mat[6] + mat[2] * rhs.mat[10] + mat[3] * rhs.mat[14];
	newMatrix.mat[3] = mat[0] * rhs.mat[3] + mat[1] * rhs.mat[7] + mat[2] * rhs.mat[11] + mat[3] * rhs.mat[15];
	newMatrix.mat[4] = mat[4] * rhs.mat[0] + mat[5] * rhs.mat[4] + mat[6] * rhs.mat[8] + mat[7] * rhs.mat[12];
	newMatrix.mat[5] = mat[4] * rhs.mat[1] + mat[5] * rhs.mat[5] + mat[6] * rhs.mat[9] + mat[7] * rhs.mat[13];
	newMatrix.mat[6] = mat[4] * rhs.mat[2] + mat[5] * rhs.mat[6] + mat[6] * rhs.mat[10] + mat[7] * rhs.mat[14];
	newMatrix.mat[7] = mat[4] * rhs.mat[3] + mat[5] * rhs.mat[7] + mat[6] * rhs.mat[11] + mat[7] * rhs.mat[15];
	newMatrix.mat[8] = mat[8] * rhs.mat[0] + mat[9] * rhs.mat[4] + mat[10] * rhs.mat[8] + mat[11] * rhs.mat[12];
	newMatrix.mat[9] = mat[8] * rhs.mat[1] + mat[9] * rhs.mat[5] + mat[10] * rhs.mat[9] + mat[11] * rhs.mat[13];
	newMatrix.mat[10] = mat[8] * rhs.mat[2] + mat[9] * rhs.mat[6] + mat[10] * rhs.mat[10] + mat[11] * rhs.mat[14];
	newMatrix.mat[11] = mat[8] * rhs.mat[3] + mat[9] * rhs.mat[7] + mat[10] * rhs.mat[11] + mat[11] * rhs.mat[15];
	newMatrix.mat[12] = mat[12] * rhs.mat[0] + mat[13] * rhs.mat[4] + mat[14] * rhs.mat[8] + mat[15] * rhs.mat[12];
	newMatrix.mat[13] = mat[12] * rhs.mat[1] + mat[13] * rhs.mat[5] + mat[14] * rhs.mat[9] + mat[15] * rhs.mat[13];
	newMatrix.mat[14] = mat[12] * rhs.mat[2] + mat[13] * rhs.mat[6] + mat[14] * rhs.mat[10] + mat[15] * rhs.mat[14];
	newMatrix.mat[15] = mat[12] * rhs.mat[3] + mat[13] * rhs.mat[7] + mat[14] * rhs.mat[11] + mat[15] * rhs.mat[15];

	return newMatrix;
}

const Matrix Matrix::operator*(const Matrix& rhs) {
	Matrix newMatrix;

	newMatrix.mat[0] = mat[0] * rhs.mat[0] + mat[1] * rhs.mat[4] + mat[2] * rhs.mat[8] + mat[3] * rhs.mat[12];
	newMatrix.mat[1] = mat[0] * rhs.mat[1] + mat[1] * rhs.mat[5] + mat[2] * rhs.mat[9] + mat[3] * rhs.mat[13];
	newMatrix.mat[2] = mat[0] * rhs.mat[2] + mat[1] * rhs.mat[6] + mat[2] * rhs.mat[10] + mat[3] * rhs.mat[14];
	newMatrix.mat[3] = mat[0] * rhs.mat[3] + mat[1] * rhs.mat[7] + mat[2] * rhs.mat[11] + mat[3] * rhs.mat[15];
	newMatrix.mat[4] = mat[4] * rhs.mat[0] + mat[5] * rhs.mat[4] + mat[6] * rhs.mat[8] + mat[7] * rhs.mat[12];
	newMatrix.mat[5] = mat[4] * rhs.mat[1] + mat[5] * rhs.mat[5] + mat[6] * rhs.mat[9] + mat[7] * rhs.mat[13];
	newMatrix.mat[6] = mat[4] * rhs.mat[2] + mat[5] * rhs.mat[6] + mat[6] * rhs.mat[10] + mat[7] * rhs.mat[14];
	newMatrix.mat[7] = mat[4] * rhs.mat[3] + mat[5] * rhs.mat[7] + mat[6] * rhs.mat[11] + mat[7] * rhs.mat[15];
	newMatrix.mat[8] = mat[8] * rhs.mat[0] + mat[9] * rhs.mat[4] + mat[10] * rhs.mat[8] + mat[11] * rhs.mat[12];
	newMatrix.mat[9] = mat[8] * rhs.mat[1] + mat[9] * rhs.mat[5] + mat[10] * rhs.mat[9] + mat[11] * rhs.mat[13];
	newMatrix.mat[10] = mat[8] * rhs.mat[2] + mat[9] * rhs.mat[6] + mat[10] * rhs.mat[10] + mat[11] * rhs.mat[14];
	newMatrix.mat[11] = mat[8] * rhs.mat[3] + mat[9] * rhs.mat[7] + mat[10] * rhs.mat[11] + mat[11] * rhs.mat[15];
	newMatrix.mat[12] = mat[12] * rhs.mat[0] + mat[13] * rhs.mat[4] + mat[14] * rhs.mat[8] + mat[15] * rhs.mat[12];
	newMatrix.mat[13] = mat[12] * rhs.mat[1] + mat[13] * rhs.mat[5] + mat[14] * rhs.mat[9] + mat[15] * rhs.mat[13];
	newMatrix.mat[14] = mat[12] * rhs.mat[2] + mat[13] * rhs.mat[6] + mat[14] * rhs.mat[10] + mat[15] * rhs.mat[14];
	newMatrix.mat[15] = mat[12] * rhs.mat[3] + mat[13] * rhs.mat[7] + mat[14] * rhs.mat[11] + mat[15] * rhs.mat[15];

	return newMatrix;
}

bool Matrix::IsIdentity() {
	bool row1 = mat[0] == 1.0f && mat[1] == 0.0f && mat[2] == 0.0f && mat[3] == 0.0f;
	bool row2 = mat[4] == 0.0f && mat[5] == 1.0f && mat[6] == 0.0f && mat[7] == 0.0f;
	bool row3 = mat[8] == 0.0f && mat[9] == 0.0f && mat[10] == 1.0f && mat[11] == 0.0f;
	bool row4 = mat[12] == 0.0f && mat[13] == 0.0f && mat[14] == 0.0f && mat[15] == 1.0f;

	return (row1 && row2 && row3 && row4);
}

float Matrix::Element(int row, int col) {
	return MATRIXELEMENT(mat, row, col);
}

Vector Matrix::Row(int row) {
	return Vector(MATRIXELEMENT(mat, row, 0), MATRIXELEMENT(mat, row, 1), MATRIXELEMENT(mat, row, 2));
}

Vector Matrix::Column(int col) {
	return Vector(MATRIXELEMENT(mat, 0, col), MATRIXELEMENT(mat, 1, col), MATRIXELEMENT(mat, 2, col));
}

void Matrix::Row(int row, Vector& value) {
	MATRIXELEMENT(mat, row, 0) = value.x;
	MATRIXELEMENT(mat, row, 1) = value.y;
	MATRIXELEMENT(mat, row, 2) = value.z;
}

void Matrix::Column(int col, Vector& value) {
	MATRIXELEMENT(mat, 0, col) = value.x;
	MATRIXELEMENT(mat, 1, col) = value.y;
	MATRIXELEMENT(mat, 2, col) = value.z;
}

void Matrix::SetTRS(Vector& position, Vector& rotation, Vector& scale) {
	*this = Matrix::TRS(position, rotation, scale);
}

Matrix Matrix::MakeScale(Vector& scale) {
	Matrix newMatrix(scale.x, 0.0f, 0.0f, 0.0f,
		0.0f, scale.y, 0.0f, 0.0f,
		0.0f, 0.0f, scale.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	return newMatrix;
}

Matrix Matrix::MakeScale(float x, float y, float z) {
	Matrix newMatrix(x, 0.0f, 0.0f, 0.0f,
		0.0f, y, 0.0f, 0.0f,
		0.0f, 0.0f, z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	return newMatrix;
}


Matrix Matrix::MakeTransform(Vector& transform) {
	Matrix newMatrix(1.0f, 0.0f, 0.0f, transform.x,
		0.0f, 1.0f, 0.0f, transform.y,
		0.0f, 0.0f, 1.0f, transform.z,
		0.0f, 0.0f, 0.0f, 1.0f);
	return newMatrix;
}

Matrix Matrix::MakeTransform(float x, float y, float z) {
	Matrix newMatrix(1.0f, 0.0f, 0.0f, x,
		0.0f, 1.0f, 0.0f, y,
		0.0f, 0.0f, 1.0f, z,
		0.0f, 0.0f, 0.0f, 1.0f);
	return newMatrix;
}


Matrix Matrix::TRS(Vector& position, Vector& rotation, Vector& scale) {
	Matrix T = Matrix::MakeTransform(position);
	Matrix R = Matrix::EulerRotation(rotation.x, rotation.y, rotation.z);
	Matrix S = Matrix::MakeScale(scale);

	return T * R * S;
}


Matrix Matrix::Perspective(float fov, float aspect, float zNear, float zFar) {
	float top = zNear * float(tanf(fov * 3.14159265f / 360.0f));
	float bottom = -1.0f * top;
	float left = bottom * aspect;
	float right = -1.0f * left;

	Matrix projectionMatrix = Matrix::identity;
	projectionMatrix.mat[0] = (2.0f * zNear) / (right - left);
	projectionMatrix.mat[5] = (2.0f * zNear) / (top - bottom);
	projectionMatrix.mat[8] = (right + left) / (right - left);
	projectionMatrix.mat[9] = (top + bottom) / (top - bottom);
	projectionMatrix.mat[10] = -1.0f * ((zFar + zNear) / (zFar - zNear));
	projectionMatrix.mat[11] = -1.0f;
	projectionMatrix.mat[14] = -1.0f * ((2.0f * (zFar + zNear)) / (zFar - zNear));
	projectionMatrix.mat[15] = 0.0f;

	return projectionMatrix;
}

Matrix Matrix::Ortho(float left, float right, float bottom, float top, float zNear, float zFar) {
	Matrix projectionMatrix = Matrix::identity;

	projectionMatrix.mat[0] = 2.0f / (right - left);
	projectionMatrix.mat[1] = 0.0f;
	projectionMatrix.mat[2] = 0.0f;
	projectionMatrix.mat[3] = 0.0f;

	projectionMatrix.mat[4] = 0.0f;
	projectionMatrix.mat[5] = 2.0f / (top - bottom);
	projectionMatrix.mat[6] = 0.0f;
	projectionMatrix.mat[7] = 0.0f;

	projectionMatrix.mat[8] = 0.0f;
	projectionMatrix.mat[9] = 0.0f;
	projectionMatrix.mat[10] = -2.0f / (zFar - zNear);
	projectionMatrix.mat[11] = 0.0f;

	projectionMatrix.mat[12] = (right + left) / (right - left);
	projectionMatrix.mat[13] = (top + bottom) / (top - bottom);
	projectionMatrix.mat[14] = (zFar + zNear) / (zFar - zNear);
	projectionMatrix.mat[15] = 1.0f;

	return projectionMatrix;
}

float Matrix::Determinant() {
#define _(x) mat[x]
	return (
		_(0) * (_(5) * (_(10) * _(15) - _(11) * _(14)) - _(6) * (_(9) * _(15) - _(11) * _(13)) + _(7) * (_(9) * _(14) - _(10) * _(13))) -
		_(1) * (_(4) * (_(10) * _(15) - _(11) * _(14)) - _(6) * (_(8) * _(15) - _(11) * _(12)) + _(7) * (_(8) * _(14) - _(10) * _(12))) +
		_(2) * (_(4) * (_(9) * _(15) - _(11) * _(13)) - _(5) * (_(8) * _(15) - _(11) * _(12)) + _(7) * (_(8) * _(13) - _(9) * _(12))) -
		_(3) * (_(4) * (_(9) * _(14) - _(10) * _(13)) - _(5) * (_(8) * _(14) - _(10) * _(12)) + _(6) * (_(8) * _(13) - _(9) * _(12)))
		);
#undef _

}

float Matrix::Determinant(Matrix& m) {
#define _(x) m.mat[x]
	return (
		_(0) * (_(5) * (_(10) * _(15) - _(11) * _(14)) - _(6) * (_(9) * _(15) - _(11) * _(13)) + _(7) * (_(9) * _(14) - _(10) * _(13))) -
		_(1) * (_(4) * (_(10) * _(15) - _(11) * _(14)) - _(6) * (_(8) * _(15) - _(11) * _(12)) + _(7) * (_(8) * _(14) - _(10) * _(12))) +
		_(2) * (_(4) * (_(9) * _(15) - _(11) * _(13)) - _(5) * (_(8) * _(15) - _(11) * _(12)) + _(7) * (_(8) * _(13) - _(9) * _(12))) -
		_(3) * (_(4) * (_(9) * _(14) - _(10) * _(13)) - _(5) * (_(8) * _(14) - _(10) * _(12)) + _(6) * (_(8) * _(13) - _(9) * _(12)))
		);
#undef _

}

Matrix Matrix::Transpose() {
	Matrix transposeMatrix;

	transposeMatrix.mat[0] = mat[0];
	transposeMatrix.mat[1] = mat[4];
	transposeMatrix.mat[2] = mat[8];
	transposeMatrix.mat[3] = mat[12];
	transposeMatrix.mat[4] = mat[1];
	transposeMatrix.mat[5] = mat[5];
	transposeMatrix.mat[6] = mat[9];
	transposeMatrix.mat[7] = mat[13];
	transposeMatrix.mat[8] = mat[2];
	transposeMatrix.mat[9] = mat[6];
	transposeMatrix.mat[10] = mat[10];
	transposeMatrix.mat[11] = mat[14];
	transposeMatrix.mat[12] = mat[3];
	transposeMatrix.mat[13] = mat[7];
	transposeMatrix.mat[14] = mat[11];
	transposeMatrix.mat[15] = mat[15];

	return transposeMatrix;
}

Matrix Matrix::Cofactor() {
#define _(x) mat[x]
#define det(_0, _1, _2, _3, _4, _5, _6, _7, _8) (_(_0) * (_(_4) * _(_8) - _(_5) * _(_7)) - _(_1) * (_(_3) * _(_8) - _(_5) * _(_6)) + _(_2) * (_(_3) * _(_7) - _(_4) * _(_6)))

	Matrix cofactorMatrix;

	cofactorMatrix.mat[0] = det(5, 6, 7, 9, 10, 11, 13, 14, 15);
	cofactorMatrix.mat[1] = det(4, 6, 7, 8, 10, 11, 12, 14, 15);
	cofactorMatrix.mat[2] = det(4, 5, 7, 8, 9, 11, 12, 13, 15);
	cofactorMatrix.mat[3] = det(4, 5, 6, 8, 9, 10, 12, 13, 14);
	cofactorMatrix.mat[4] = det(1, 2, 3, 9, 10, 11, 13, 14, 15);
	cofactorMatrix.mat[5] = det(0, 2, 3, 8, 10, 11, 12, 14, 15);
	cofactorMatrix.mat[6] = det(0, 1, 3, 8, 9, 11, 12, 13, 15);
	cofactorMatrix.mat[7] = det(0, 1, 2, 8, 9, 10, 12, 13, 14);
	cofactorMatrix.mat[8] = det(1, 2, 3, 5, 6, 7, 13, 14, 15);
	cofactorMatrix.mat[9] = det(0, 2, 3, 4, 6, 7, 12, 14, 15);
	cofactorMatrix.mat[10] = det(0, 1, 3, 4, 5, 7, 12, 13, 15);
	cofactorMatrix.mat[11] = det(0, 1, 2, 4, 5, 6, 12, 13, 14);
	cofactorMatrix.mat[12] = det(1, 2, 3, 5, 6, 7, 9, 10, 11);
	cofactorMatrix.mat[13] = det(0, 2, 3, 4, 6, 7, 8, 10, 11);
	cofactorMatrix.mat[14] = det(0, 1, 3, 4, 5, 7, 8, 9, 11);
	cofactorMatrix.mat[15] = det(0, 1, 2, 4, 5, 6, 8, 9, 10);

	return cofactorMatrix;
#undef det
#undef _
}

Matrix Matrix::Adjoint() {
#define _(x) mat[x]
#define det(_0, _1, _2, _3, _4, _5, _6, _7, _8) (_(_0) * (_(_4) * _(_8) - _(_5) * _(_7)) - _(_1) * (_(_3) * _(_8) - _(_5) * _(_6)) + _(_2) * (_(_3) * _(_7) - _(_4) * _(_6)))

	Matrix transposedCofactorMatrix;

	transposedCofactorMatrix.mat[0] = (det(5, 6, 7, 9, 10, 11, 13, 14, 15));
	transposedCofactorMatrix.mat[4] = -1 * (det(4, 6, 7, 8, 10, 11, 12, 14, 15));
	transposedCofactorMatrix.mat[8] = (det(4, 5, 7, 8, 9, 11, 12, 13, 15));
	transposedCofactorMatrix.mat[12] = -1 * (det(4, 5, 6, 8, 9, 10, 12, 13, 14));
	transposedCofactorMatrix.mat[1] = -1 * (det(1, 2, 3, 9, 10, 11, 13, 14, 15));
	transposedCofactorMatrix.mat[5] = (det(0, 2, 3, 8, 10, 11, 12, 14, 15));
	transposedCofactorMatrix.mat[9] = -1 * (det(0, 1, 3, 8, 9, 11, 12, 13, 15));
	transposedCofactorMatrix.mat[13] = (det(0, 1, 2, 8, 9, 10, 12, 13, 14));
	transposedCofactorMatrix.mat[2] = (det(1, 2, 3, 5, 6, 7, 13, 14, 15));
	transposedCofactorMatrix.mat[6] = -1 * (det(0, 2, 3, 4, 6, 7, 12, 14, 15));
	transposedCofactorMatrix.mat[10] = (det(0, 1, 3, 4, 5, 7, 12, 13, 15));
	transposedCofactorMatrix.mat[14] = -1 * (det(0, 1, 2, 4, 5, 6, 12, 13, 14));
	transposedCofactorMatrix.mat[3] = -1 * (det(1, 2, 3, 5, 6, 7, 9, 10, 11));
	transposedCofactorMatrix.mat[7] = (det(0, 2, 3, 4, 6, 7, 8, 10, 11));
	transposedCofactorMatrix.mat[11] = -1 * (det(0, 1, 3, 4, 5, 7, 8, 9, 11));
	transposedCofactorMatrix.mat[15] = (det(0, 1, 2, 4, 5, 6, 8, 9, 10));

	return transposedCofactorMatrix;

#undef det
#undef _
}

Matrix Matrix::Inverse() {
	float determinant = this->Determinant();
	Matrix adjoint = this->Adjoint();

	return (1.0f / determinant) * adjoint;
}

Matrix& Matrix::operator*=(const float rhs) {
	Matrix newMatrix;

	newMatrix.mat[0] = mat[0] * rhs;
	newMatrix.mat[1] = mat[1] * rhs;
	newMatrix.mat[2] = mat[2] * rhs;
	newMatrix.mat[3] = mat[3] * rhs;
	newMatrix.mat[4] = mat[4] * rhs;
	newMatrix.mat[5] = mat[5] * rhs;
	newMatrix.mat[6] = mat[6] * rhs;
	newMatrix.mat[7] = mat[7] * rhs;
	newMatrix.mat[8] = mat[8] * rhs;
	newMatrix.mat[9] = mat[9] * rhs;
	newMatrix.mat[10] = mat[10] * rhs;
	newMatrix.mat[11] = mat[11] * rhs;
	newMatrix.mat[12] = mat[12] * rhs;
	newMatrix.mat[13] = mat[13] * rhs;
	newMatrix.mat[14] = mat[14] * rhs;
	newMatrix.mat[15] = mat[15] * rhs;

	*this = newMatrix;
	return *this;
}

const Matrix Matrix::operator*(const float rhs) {
	Matrix newMatrix;

	newMatrix.mat[0] = mat[0] * rhs;
	newMatrix.mat[1] = mat[1] * rhs;
	newMatrix.mat[2] = mat[2] * rhs;
	newMatrix.mat[3] = mat[3] * rhs;
	newMatrix.mat[4] = mat[4] * rhs;
	newMatrix.mat[5] = mat[5] * rhs;
	newMatrix.mat[6] = mat[6] * rhs;
	newMatrix.mat[7] = mat[7] * rhs;
	newMatrix.mat[8] = mat[8] * rhs;
	newMatrix.mat[9] = mat[9] * rhs;
	newMatrix.mat[10] = mat[10] * rhs;
	newMatrix.mat[11] = mat[11] * rhs;
	newMatrix.mat[12] = mat[12] * rhs;
	newMatrix.mat[13] = mat[13] * rhs;
	newMatrix.mat[14] = mat[14] * rhs;
	newMatrix.mat[15] = mat[15] * rhs;

	return newMatrix;
}

const Matrix operator*(float rhs, const Matrix& lhs) {
	Matrix newMatrix;

	newMatrix.mat[0] = lhs.mat[0] * rhs;
	newMatrix.mat[1] = lhs.mat[1] * rhs;
	newMatrix.mat[2] = lhs.mat[2] * rhs;
	newMatrix.mat[3] = lhs.mat[3] * rhs;
	newMatrix.mat[4] = lhs.mat[4] * rhs;
	newMatrix.mat[5] = lhs.mat[5] * rhs;
	newMatrix.mat[6] = lhs.mat[6] * rhs;
	newMatrix.mat[7] = lhs.mat[7] * rhs;
	newMatrix.mat[8] = lhs.mat[8] * rhs;
	newMatrix.mat[9] = lhs.mat[9] * rhs;
	newMatrix.mat[10] = lhs.mat[10] * rhs;
	newMatrix.mat[11] = lhs.mat[11] * rhs;
	newMatrix.mat[12] = lhs.mat[12] * rhs;
	newMatrix.mat[13] = lhs.mat[13] * rhs;
	newMatrix.mat[14] = lhs.mat[14] * rhs;
	newMatrix.mat[15] = lhs.mat[15] * rhs;

	return newMatrix;
}

Matrix operator*(float rhs, Matrix& lhs) {
	Matrix newMatrix;

	newMatrix.mat[0] = lhs.mat[0] * rhs;
	newMatrix.mat[1] = lhs.mat[1] * rhs;
	newMatrix.mat[2] = lhs.mat[2] * rhs;
	newMatrix.mat[3] = lhs.mat[3] * rhs;
	newMatrix.mat[4] = lhs.mat[4] * rhs;
	newMatrix.mat[5] = lhs.mat[5] * rhs;
	newMatrix.mat[6] = lhs.mat[6] * rhs;
	newMatrix.mat[7] = lhs.mat[7] * rhs;
	newMatrix.mat[8] = lhs.mat[8] * rhs;
	newMatrix.mat[9] = lhs.mat[9] * rhs;
	newMatrix.mat[10] = lhs.mat[10] * rhs;
	newMatrix.mat[11] = lhs.mat[11] * rhs;
	newMatrix.mat[12] = lhs.mat[12] * rhs;
	newMatrix.mat[13] = lhs.mat[13] * rhs;
	newMatrix.mat[14] = lhs.mat[14] * rhs;
	newMatrix.mat[15] = lhs.mat[15] * rhs;

	return newMatrix;
}

Matrix Matrix::MakeXRotation(float degrees) {
	Matrix rotation = Matrix::identity;

	degrees *= 0.0174532925f; // To radians!

	rotation[5] = cosf(degrees);
	rotation[6] = sinf(degrees);
	rotation[9] = -1.0f * sin(degrees);
	rotation[10] = cosf(degrees);

	return rotation;
}

Matrix Matrix::MakeYRotation(float degrees) {
	Matrix rotation = Matrix::identity;

	degrees *= 0.0174532925f; // To radians!

	rotation[0] = cosf(degrees);
	rotation[2] = -1.0f * sinf(degrees);
	rotation[8] = sinf(degrees);
	rotation[10] = cosf(degrees);

	return rotation;
}

Matrix Matrix::MakeZRotation(float degrees) {
	Matrix rotation = Matrix::identity;

	degrees *= 0.0174532925f; // To radians!

	rotation[0] = cosf(degrees);
	rotation[1] = sinf(degrees);
	rotation[4] = -sinf(degrees);
	rotation[5] = cosf(degrees);

	return rotation;
}

Matrix Matrix::AxisAngleRotation(Vector& rotate, float degrees) {
	Vector nr = rotate.Normalized();
#define x nr.x
#define y nr.y
#define z nr.z
	degrees *= 0.0174532925f; // To radians!

	float c, s, t;

	c = cos(degrees);
	s = sin(degrees);
	t = 1 - c;

	Matrix rotation = Matrix::identity;

	rotation.mat[0] = t * x * x + c;
	rotation.mat[1] = t * x * y - s * z;
	rotation.mat[2] = t * x * z + s * y;

	rotation.mat[4] = t * x * y + s * z;
	rotation.mat[5] = t * y * y + c;
	rotation.mat[6] = t * y * z - s * x;

	rotation.mat[8] = t * x * z - s * y;
	rotation.mat[9] = t * y * z + s * x;
	rotation.mat[10] = t * z * z + c;

	return rotation;
#undef x
#undef y
#undef z
}

Matrix Matrix::EulerRotation(float x, float y, float z) {
	x *= 0.0174532925f; // To radians!
	y *= 0.0174532925f; // To radians!
	z *= 0.0174532925f; // To radians!

	float a = cosf(x);
	float b = sinf(x);
	float c = cosf(y);
	float d = sinf(y);
	float e = cosf(z);
	float f = sinf(z);

	float ad = a * d;
	float bd = b * d;

	Matrix rotation = Matrix::identity;

	rotation.mat[0] = c * e;
	rotation.mat[1] = c * f;
	rotation.mat[2] = -1.0f * d;
	rotation.mat[4] = bd * e + a * (-1.0f * f);
	rotation.mat[5] = bd * f + a * e;
	rotation.mat[6] = b * c;
	rotation.mat[8] = ad * e + (-1.0f * b) * (-1.0f * f);
	rotation.mat[9] = ad * f + (-1.0f * b) * e;
	rotation.mat[10] = a * c;

	return rotation;
}

Vector Matrix::operator*(Vector& v) {
	float x = v.x * mat[0] + v.y * mat[1] + v.z * mat[2];
	float y = v.x * mat[4] + v.y * mat[5] + v.z * mat[6];
	float z = v.x * mat[8] + v.y * mat[9] + v.z * mat[10];

	return Vector(x, y, z);
}

const Vector Matrix::operator*(const Vector& v) {
	float x = v.x * mat[0] + v.y * mat[1] + v.z * mat[2];
	float y = v.x * mat[4] + v.y * mat[5] + v.z * mat[6];
	float z = v.x * mat[8] + v.y * mat[9] + v.z * mat[10];

	return Vector(x, y, z);
}

const Vector operator*(Vector& v, const Matrix& m) {
	float x = v.x * m.mat[0] + v.y * m.mat[1] + v.z * m.mat[2];
	float y = v.x * m.mat[4] + v.y * m.mat[5] + v.z * m.mat[6];
	float z = v.x * m.mat[8] + v.y * m.mat[9] + v.z * m.mat[10];

	return Vector(x, y, z);
}

Vector operator*(Vector& v, Matrix& m) {
	float x = v.x * m.mat[0] + v.y * m.mat[1] + v.z * m.mat[2];
	float y = v.x * m.mat[4] + v.y * m.mat[5] + v.z * m.mat[6];
	float z = v.x * m.mat[8] + v.y * m.mat[9] + v.z * m.mat[10];

	return Vector(x, y, z);
}

float& Matrix::operator[](int i) {
	return mat[i];
}