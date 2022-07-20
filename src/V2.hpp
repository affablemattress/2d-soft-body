#pragma once
#include <math.h>

class V2 {
public:
	float x;
	float y;
	V2(float X = 0, float Y = 0);

	static V2 Normalized(V2 u);
	static float Dot(V2 u, V2 v);
	static float Distance(V2 u, V2 v);
	V2 operator+(V2 v);
	V2 operator-(V2 v);
	V2 operator*(float scalar);
	V2 operator/(float scalar);

	void Normalize();
	float Length();
};