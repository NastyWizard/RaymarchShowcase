#pragma once
#include "Math/VectorMath.h"

class Color
{
public:
	Color() { Set(1.f, 1.f, 1.f, 1.f); }
	~Color();

	void Set(float r, float g, float b, float a) { this->r = r; this->g = g; this->b = b; this->a = a; }
	void Set(vec4 v) { this->r = v.x; this->g = v.y; this->b = v.z; this->a = v.w; }

private:

	// variables
public:
	float r, g, b, a;

private:

};