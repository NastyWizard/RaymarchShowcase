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
	
	// returns quaternion from given angle(deg) and axis. angle must be in radians
	static Quaternion AngleAxis(float angle, vec3 axis)
	{
		
		float h = .5f * angle;
		Quaternion q;
		q.w = angle;//cos(h);
		q.v = axis.GetNormalized();//sin(h) * axis.GetNormalized();
		return q;
	}

	// set quaternion from given angle(deg) and axis. angle must be in radians
	void SetAngleAxis(float angle, vec3 axis)
	{
		*this = AngleAxis(angle, axis);
	}

	// angle is returned in radians
	void GetAngleAxis(float &angle, vec3 &axis) 
	{
		if (v.GetLength() <= FLT_EPSILON || abs(w) <= FLT_EPSILON)
		{
			angle = 0;
			axis.Set(0, 0, 1);
			return;
		}

		angle = w;// 2.f * acosf(w);
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

	Quaternion& operator=(Quaternion q) 
	{
		w = q.w;
		v = q.v;
		return *this;
	}

};

typedef Quaternion quat;