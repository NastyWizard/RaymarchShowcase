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
	d.Normalize();

	mat4x4 nMat;
	nMat.SetIdentity();
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
}

void Transform::Translate()
{
	mat4x4 nMat;
	nMat.SetIdentity();

	nMat[12] = position.x;
	nMat[13] = position.y;
	nMat[14] = position.z;
	matrix *= nMat;
}

mat4x4 Transform::GetMatrix()
{
	matrix.SetIdentity();

	Scale();
	Rotate();
	Translate();
	//matrix.SetIndex(); // this is to draw the indices in the shader.
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
}