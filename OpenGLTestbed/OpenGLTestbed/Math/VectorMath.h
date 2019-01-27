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

	Vector2(float x, float y) { this->x = x; this->y = y; }

	Vector2() { Set(Zero()); }

	static Vector2 Zero() { return Vector2(0, 0); }

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

	void Normalize() {Set(GetNormalized());}

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
		return *this;
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

	Vector3(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }

	Vector3(float x) { this->x = x; this->y = x; this->z = x; }


	Vector3() { Set(Zero()); }

	static Vector3 Zero() { return Vector3(0, 0, 0); }
	static Vector3 One() { return Vector3(1, 1, 1); }
	static Vector3 UnitX() { return Vector3(1, 0, 0); }
	static Vector3 UnitY() { return Vector3(0, 1, 0); }
	static Vector3 UnitZ() { return Vector3(0, 0, 1); }

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

		float l = GetLength();

		if (l != 0.0f)
		{
			norm /= l;
		}
		else 
		{
			norm.Set(Vector3::Zero());
		}
		return norm;
	}

	// Magnitude
	float GetLength()
	{
		return sqrtf((x*x) + (y*y) + (z*z));
	}

	// operator overloads

	void operator=(const Vector3 &vec)
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

	Vector4(float x, float y, float z, float w) { this->x = x; this->y = y; this->z = z; this->w = w; }

	Vector4() { Set(Zero()); }

	static Vector4 Zero() { return Vector4(0, 0, 0, 0); }

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
		return *this;
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


typedef Vector2 float2;
typedef Vector3 float3;
typedef Vector4 float4;


inline Vector2 operator*(float n, const vec2& v)
{
	Vector2 nVec;
	nVec.x = v.x * n;
	nVec.y = v.y * n;
	return nVec;
}

inline Vector3 operator*(float n, const Vector3& v)
{
	Vector3 nVec;
	nVec.x = v.x * n;
	nVec.y = v.y * n;
	nVec.z = v.z * n;
	return nVec;
}

inline Vector4 operator*(float n, const vec4& v)
{
	Vector4 nVec;
	nVec.x = v.x * n;
	nVec.y = v.y * n;
	nVec.z = v.z * n;
	nVec.w = v.w * n;
	return nVec;
}