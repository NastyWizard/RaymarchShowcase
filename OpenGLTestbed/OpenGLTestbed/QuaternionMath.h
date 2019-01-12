#pragma once
#include "VectorMath.h"

class Quaternion 
{
private:
	vec3 eulerAngles;
public:
	Quaternion();
	~Quaternion();

	static Quaternion Identity() 
	{
		Quaternion q;
		q.SetEulerAnles(vec3(0, 0, 0));
		return q;
	}

	void SetEulerAnles(vec3 v) { eulerAngles = v; }

	vec3 GetEulerAngles() { return eulerAngles; }

};

typedef Quaternion quat;