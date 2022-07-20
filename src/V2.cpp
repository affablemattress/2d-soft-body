#include "V2.hpp"

V2::V2(double X, double Y) {
	x = X;
	y = Y;
}

V2 V2::Normalized(V2 u) {
	double ratio = 1 / sqrt(u.x * u.x + u.y * u.y);
	return V2(u.x * ratio, u.y * ratio);
}

double V2::Dot(V2 u, V2 v) {
	return u.x * v.x + u.y * v.y;
}

double V2::Distance(V2 u, V2 v) {
	return sqrt(pow(u.x - v.x, 2) + pow(u.y - v.y, 2));
}

V2 V2::operator+(V2 v) {
	return V2(x + v.x, y + v.y);
}

V2 V2::operator-(V2 v) {
	return V2(x - v.x, y - v.y);
}

V2 V2::operator*(double scalar) {
	return V2(x * scalar, y * scalar);
}

V2 V2::operator/(double scalar) {
	return V2(x / scalar, y / scalar);
}


void V2::Normalize() {
	double ratio = 1 / sqrt(x * x + y * y);
	x *= ratio;
	y *= ratio;
}

double V2::Length() {
	return sqrt(x * x + y * y);
}