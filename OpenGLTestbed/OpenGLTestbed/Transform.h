#pragma once
#include "VectorMath.h"
#include "Quaternion.h"

class Transform 
{
public:
	vec3 position;
	quat rotation;
	vec3 scale;
};