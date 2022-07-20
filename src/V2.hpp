#pragma once
#include <math.h>

class V2 {
public:
	double x;
	double y;
	V2(double X = 0, double Y = 0);

	static V2 Normalized(V2 u);
	static double Dot(V2 u, V2 v);
	static double Distance(V2 u, V2 v);
	V2 operator+(V2 v);
	V2 operator-(V2 v);
	V2 operator*(double scalar);
	V2 operator/(double scalar);

	void Normalize();
	double Length();
};