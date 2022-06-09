#pragma once

#include "vector.h"

class Matrix {
public:
	float mat[16];
public:
	Matrix();
	Matrix(float _0, float _1, float _2, float _3, float _4, float _5, float _6, float _7, float _8, float _9, float _10, float _11, float _12, float _13, float _14, float _15);
	~Matrix();
	Matrix(const Matrix& m);
	Matrix& operator=(const Matrix& m);

	Matrix& operator*=(Matrix& rhs);
	Matrix& operator*=(const Matrix& rhs);
	Matrix operator*(Matrix& rhs);
	const Matrix operator*(const Matrix& rhs);
	Matrix& operator*=(const float rhs);
	const Matrix operator*(const float rhs);
	Vector operator*(Vector& v);
	const Vector operator*(const Vector& v);
	float& operator[](int i);

	Matrix Transpose();
	Matrix Inverse();
	Matrix Cofactor();
	Matrix Adjoint();
	float Determinant();
	bool IsIdentity();

	float Element(int row, int col);
	Vector Row(int row);
	Vector Column(int col);
	void Row(int row, Vector& value);
	void Column(int col, Vector& value);

	void SetTRS(Vector& position, Vector& rotation, Vector& scale);

	static Matrix AxisAngleRotation(Vector& rotate, float degrees);
	static Matrix EulerRotation(float x, float y, float z);
	static Matrix MakeXRotation(float degrees);
	static Matrix MakeYRotation(float degrees);
	static Matrix MakeZRotation(float degrees);
	static Matrix MakeScale(Vector& scale);
	static Matrix MakeScale(float x, float y, float z);
	static Matrix MakeTransform(Vector& transform);
	static Matrix MakeTransform(float x, float y, float z);
	static Matrix TRS(Vector& position, Vector& rotation, Vector& scale);
	static Matrix Ortho(float left, float right, float bottom, float top, float zNear, float zFar);
	static Matrix Perspective(float fov, float aspect, float zNear, float zFar);
	static float Determinant(Matrix& m);

	static const Matrix zero;
	static const Matrix identity;
};

const Matrix operator*(float lhs, const Matrix& rhs);
Matrix operator*(float lhs, Matrix& rhs);
const Vector operator*(Vector& v, const Matrix& m);
Vector operator*(Vector& v, Matrix& m);

