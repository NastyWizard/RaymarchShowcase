#pragma once
#include "Helpers.h"
#include "VectorMath.h"

class Quaternion 
{
private:
public:
	float w;
	vec3 v;
	Quaternion();
	~Quaternion();
	
	// returns quaternion from given angle(deg) and axis.
	static Quaternion AngleAxis(float angle, vec3 axis)
	{
		
		float h = DegToRad(.5f * angle);
		Quaternion q;
		q.w = cos(h);
		q.v = sin(h) * axis.GetNormalized();
		return q;
	}

	// set quaternion from given angle(deg) and axis.
	void SetAngleAxis(float angle, vec3 axis)
	{
		float h = DegToRad(.5f * angle);
		w = cos(h);
		v = sin(h) * axis.GetNormalized();
	}

	void GetAngleAxis(float &angle, vec3 &axis) 
	{
		angle = RadToDeg(2.f * acosf(w));
		axis = v.GetNormalized();
	}

	//static Quaternion Identity() 
	//{
	//	Quaternion q;
	//	q.x = q.y = q.z = 0.f;
	//	return q;
	//}

	//void SetEulerAngles(vec3 v) { eulerAngles = v; }
	//
	//vec3 GetEulerAngles() { return eulerAngles; }

};

typedef Quaternion quat;