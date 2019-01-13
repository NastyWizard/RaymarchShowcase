#include "Transform.h"

void Transform::Scale()
{
	mat4x4 nMat;
	nMat.SetIdentity();

	nMat[0] = scale.x;
	nMat[5] = scale.y;
	nMat[10] = scale.z;
	matrix *= nMat;
}

void Transform::Rotate()
{
	vec3 d;
	float a;

	rotation.GetAngleAxis(a, d);

	mat4x4 nMat;
	// 11 12 13
	nMat[0] = cosf(a) + d.x*d.x*(1.f - cosf(a));
	nMat[1] = d.x*d.y*(1.f - cosf(a)) - d.z*sinf(a);
	nMat[2] = d.x*d.z*(1.f - cosf(a)) + d.y*sinf(a);

	// 21 22 23
	nMat[0 + 4] = d.y*d.x*(1.f - cosf(a)) + d.z*sinf(a);
	nMat[1 + 4] = cosf(a) + d.y*d.y*(1.f - cosf(a));
	nMat[2 + 4] = d.y*d.z*(1.f - cosf(a)) - d.x*sinf(a);

	// 31 32 33
	nMat[0 + 8] = d.z*d.x*(1.f - cosf(a)) - d.y*sinf(a);
	nMat[1 + 8] = d.z*d.y*(1.f - cosf(a)) + d.x * sinf(a);
	nMat[2 + 8] = cosf(a) + d.z*d.z*(1.f - cos(a));

	matrix *= nMat;

	//x = euler.x;
	//y = euler.y;
	//z = euler.z;
	//
	//
	//
	//// x axis rotation
	//nMat.SetIdentity();
	//	nMat[5]  = cosf(euler.x);
	//	nMat[6]  = -sinf(euler.x);
	//	nMat[9]  = sinf(euler.x);
	//	nMat[10] = cosf(euler.x);
	//matrix *= nMat;
	//// y axis rotation
	//nMat.SetIdentity();
	//	nMat[0]	 = cosf(euler.y);
	//	nMat[2]	 = sinf(euler.y);
	//	nMat[8] = -sinf(euler.y);
	//	nMat[10] = cosf(euler.y);
	//matrix *= nMat;
	//// z axis rotation
	//nMat.SetIdentity();
	//	nMat[0]	= cosf(euler.z);
	//	nMat[1] = -sinf(euler.z);
	//	nMat[4]	= sinf(euler.z);
	//	nMat[5]	= cosf(euler.z);
	//matrix *= nMat;
}

void Transform::Translate()
{
	mat4x4 nMat;
	nMat.SetIdentity();

	nMat[3] = position.x;
	nMat[7] = position.y;
	nMat[11] = position.z;
	matrix *= nMat;
}

mat4x4 Transform::GetMatrix()
{
	matrix.SetIdentity();

	Scale();
	Rotate();
	Translate();

	return matrix;

	//mat[15] = 1.0f;
	//// TRANSLATION
	//mat[3] = position.x;
	//mat[7] = position.y;
	//mat[11] = position.z;
	//// SCALE
	//mat[0] = scale.x;
	//mat[5] = scale.y;
	//mat[10] = scale.z;
	// ROTATION








	;



	;


}