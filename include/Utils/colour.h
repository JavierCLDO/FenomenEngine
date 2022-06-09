#pragma once

struct Colour {
	double r, g, b, a;

	Colour(double r = 1.0, double g = 1.0, double b = 1.0, double a = 1.0) : r(r), g(g), b(b), a(a) {}

	inline Colour operator*(const double scalar) {
		return Colour(r * scalar, g * scalar, b * scalar, a * scalar);
	}
};