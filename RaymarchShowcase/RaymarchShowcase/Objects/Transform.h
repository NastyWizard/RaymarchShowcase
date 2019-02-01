#pragma once
#include "..\Math\VectorMath.h"
#include "..\Math\QuaternionMath.h"
#include "..\Math\MatrixMath.h"

class Transform 
{
	// variables
private:
	mat4x4 matrix;
public:
	vec3 position = vec3::Zero();
	quat rotation = quat::Identity();
	vec3 scale = vec3::One();

	// functions
private:
	void Scale();
	void Rotate();
	void Translate ();
public:

	mat4x4 GetMatrix();
};