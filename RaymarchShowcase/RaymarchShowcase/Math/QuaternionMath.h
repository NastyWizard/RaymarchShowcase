#pragma once
#include "..\Util\Helpers.h"
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
		q.w = cos(h);
		q.v = sin(h) * axis.GetNormalized();
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
			// identity
			angle = 0;
			axis.Set(0, 0, 1);
			return;
		}

		angle = 2.f * acosf(w);
		axis = asinf(w) * v.GetNormalized();
	}

	static Quaternion Identity() 
	{
		Quaternion q;
		
		q.v.Set(0.0f, 0.0f, 1.0f);
		q.w = 0.0f;
		
		return q;
	}

	Quaternion& operator=(Quaternion q) 
	{
		w = q.w;
		v = q.v;
		return *this;
	}

};

typedef Quaternion quat;