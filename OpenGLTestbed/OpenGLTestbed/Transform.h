#pragma once
#include "VectorMath.h"
#include "QuaternionMath.h"
#include "MatrixMath.h"

class Transform 
{
	// variables
private:
	
public:
	vec3 position = vec3::Zero();
	quat rotation = quat::Identity();
	vec3 scale = vec3::One();

	mat4x4 GetMatrix() 
	{
		mat4x4 mat;
		mat.SetIdentity();
		vec3 euler = rotation.GetEulerAngles();

		mat[15] = 1.0f;
		// TRANSLATION
		mat[3]  = position.x;
		mat[7]  = position.y;
		mat[11] = position.z;
		// SCALE
		mat[0]  = scale.x;
		mat[5]  = scale.y;
		mat[10] = scale.z;
		// ROTATION
		// x axis rotation
		//mat[5]  += cosf(euler.x);
		//mat[6]  += -sinf(euler.x);
		//mat[9]  += sinf(euler.x);
		//mat[10] += cosf(euler.x);
		// y axis rotation
		//mat[0]	+= cosf(euler.y);
		//mat[2]	+= sinf(euler.y);
		//mat[8]	+= -sinf(euler.y);
		//mat[10] += cosf(euler.y);
		// z axis rotation
		//mat[0]	+= cosf(euler.z);
		//mat[1]	+= -sinf(euler.z);
		//mat[4]	+= sinf(euler.z);
		//mat[5]	+= cosf(euler.z);
		return mat;
	}	



	// functions
private:
public:
};