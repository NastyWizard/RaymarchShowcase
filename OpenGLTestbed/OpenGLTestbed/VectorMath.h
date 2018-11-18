#pragma once
#include <math.h>
class Vector2
{
	// variables
private:
public:
	float x, y;

	// functions
private:
public:
	static float Dot(Vector2 a, Vector2 b)
	{
		float dp = (a.x * b.x) + (a.y * b.y);
		return dp;
	}

	void Set(float X, float Y)
	{
		x = X;
		y = Y;
	}

	void Set(Vector2 v)
	{
		Set(v.x, v.y);
	}

	void Normalize() { Set(GetNormalized()); }

	Vector2 GetNormalized()
	{
		Vector2 norm;
		norm.Set(x, y);
		norm /= GetLength();
		return norm;
	}

	// Magnitude
	float GetLength()
	{
		return sqrt((x*x) + (y*y));
	}

	// operator overloads

	Vector2& operator=(const Vector2 &vec)
	{
		Set(vec);
	}

	Vector2 operator*(float n)
	{
		Vector2 nVec;
		nVec.x = x * n;
		nVec.y = y * n;
		return nVec;
	}
	Vector2 operator/(float n)
	{
		Vector2 nVec;
		nVec.x = x / n;
		nVec.y = y / n;
		return nVec;
	}
	Vector2& operator*=(float n)
	{
		this->x *= n;
		this->y *= n;
		return *this;
	}
	Vector2& operator/=(float n)
	{
		this->x /= n;
		this->y /= n;
		return *this;
	}
};
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
class Vector3
{
	// variables
private:
public:
	float x, y, z;

	// functions
private:
public:
	static float Dot(Vector3 a, Vector3 b)
	{
		float dp = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
		return dp;
	}

	static Vector3 Cross(Vector3 a, Vector3 b) 
	{
		Vector3 cross;
		cross.x = (a.y * b.z) - (a.z * b.y);
		cross.y = (a.z * b.x) - (a.x * b.z);
		cross.z = (a.x * b.y) - (a.y * b.x);
		return cross;
	}

	void Set(float X, float Y, float Z)
	{
		x = X;
		y = Y;
		z = Z;
	}

	void Set(Vector3 v)
	{
		Set(v.x, v.y, v.z);
	}

	void Set(Vector2 v, float Z)
	{
		Set(v.x, v.y, Z);
	}

	void Normalize() { Set(GetNormalized()); }

	Vector3 GetNormalized()
	{
		Vector3 norm;
		norm.Set(x, y, z);
		norm /= GetLength();
		return norm;
	}

	// Magnitude
	float GetLength()
	{
		return sqrt((x*x) + (y*y) + (z*z));
	}

	// operator overloads

	Vector3& operator=(const Vector3 &vec)
	{
		Set(vec);
	}

	Vector3 operator*(float n)
	{
		Vector3 nVec;
		nVec.x = x * n;
		nVec.y = y * n;
		nVec.z = z * n;
		return nVec;
	}
	Vector3 operator/(float n)
	{
		Vector3 nVec;
		nVec.x = x / n;
		nVec.y = y / n;
		nVec.z = z / n;
		return nVec;
	}
	Vector3& operator*=(float n)
	{
		x *= n;
		y *= n;
		z *= n;
		return *this;
	}
	Vector3& operator/=(float n)
	{
		x /= n;
		y /= n;
		z /= n;
		return *this;
	}
};


typedef Vector2 vec2;
typedef Vector3 vec3;
