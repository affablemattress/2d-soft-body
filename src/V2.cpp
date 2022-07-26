#include "V2.h"
#include <math.h>

double V2::Magnitude(const V2& u) {
	return sqrt(u.GetX() * u.GetX() + u.GetY() * u.GetY());
}
double V2::SqrMagnitude(const V2& u) {
	return u.GetX() * u.GetX() + u.GetY() * u.GetY();
}
V2 V2::Normalized(const V2& u) {
	double factor = 1 / V2::Magnitude(u);
	return u * factor;
}
double V2::Dot(const V2& u, const V2& v) {
	return u.GetX() * v.GetX() + v.GetY() * v.GetY();
}

V2 V2::operator+(const V2& v) const {
	return V2(x_ + v.GetX(), y_ + v.GetY());
}
V2 V2::operator-(const V2& v) const {
	return V2(x_ - v.GetX(), y_ - v.GetY());
}
V2 V2::operator-() const {
	return V2(-x_, -y_);
}
V2 V2::operator*(double c) const {
	return V2(x_ * c, y_ * c);
}
V2 V2::operator/(double c) const {
	return V2(x_ / c, y_ / c);
}

double V2::GetX() const { return x_; }
void V2::SetX(double x) {
	x_ = x;
}
double V2::GetY() const { return y_; }
void V2::SetY(double y) {
	y_ = y;
}

V2::V2() 
	: x_(0), y_(0) {}
V2::V2(double x, double y) 
	: x_(x), y_(y) {}
V2::~V2() {}