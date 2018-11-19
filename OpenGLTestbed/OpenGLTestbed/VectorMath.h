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
		return sqrtf((x*x) + (y*y));
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
		return sqrtf((x*x) + (y*y) + (z*z));
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
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
class Vector4
{
	// variables
private:
public:
	float x, y, z, w;

	// functions
private:
public:
	static float Dot(Vector4 a, Vector4 b)
	{
		float dp = (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
		return dp;
	}

	void Set(float X, float Y, float Z, float W)
	{
		x = X;
		y = Y;
		z = Z;
		w = W;
	}

	void Set(Vector4 v)
	{
		Set(v.x, v.y, v.z, v.w);
	}

	void Set(Vector2 v, float Z, float W)
	{
		Set(v.x, v.y, Z, W);
	}

	void Set(Vector2 v, Vector2 v2)
	{
		Set(v.x, v.y, v2.x, v2.y);
	}

	void Set(Vector3 v, float W)
	{
		Set(v.x, v.y, v.z, W);
	}

	void Normalize() { Set(GetNormalized()); }

	Vector4 GetNormalized()
	{
		Vector4 norm;
		norm.Set(x, y, z, w);
		norm /= GetLength();
		return norm;
	}

	// Magnitude
	float GetLength()
	{
		return sqrtf((x*x) + (y*y) + (z*z) + (w*w));
	}

	// operator overloads

	Vector4& operator=(const Vector4 &vec)
	{
		Set(vec);
	}

	Vector4 operator*(float n)
	{
		Vector4 nVec;
		nVec.x = x * n;
		nVec.y = y * n;
		nVec.z = z * n;
		nVec.w = w * n;
		return nVec;
	}
	Vector4 operator/(float n)
	{
		Vector4 nVec;
		nVec.x = x / n;
		nVec.y = y / n;
		nVec.z = z / n;
		nVec.w = w / n;
		return nVec;
	}
	Vector4& operator*=(float n)
	{
		x *= n;
		y *= n;
		z *= n;
		w *= n;
		return *this;
	}
	Vector4& operator/=(float n)
	{
		x /= n;
		y /= n;
		z /= n;
		w /= n;
		return *this;
	}
};


typedef Vector2 vec2;
typedef Vector3 vec3;
typedef Vector4 vec4;
