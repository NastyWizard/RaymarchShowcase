
#ifndef _DEFAULT_INCLUDES_
#define _DEFAULT_INCLUDES_

#define PI 3.14159265359

#define INFINITY 1.0 / 0.0
#define FLT_MAX 3.402823466e+38
#define FLT_MIN 1.175494351e-38

uniform float time;
uniform vec2 resolution;

float maxcomp2(vec2 a) { return max(a.x,a.y); }

vec3 rotateX(vec3 p, float angle)
{
	mat3x3 rMat;
	rMat[0] = vec3(1., 0., 0.);
	rMat[1] = vec3(0., cos(angle), sin(angle));
	rMat[2] = vec3(0., -sin(angle), cos(angle));
	return rMat * p;
}
vec3 rotateY(vec3 p, float angle)
{
	mat3x3 rMat;
	rMat[0] = vec3(cos(angle), 0., -sin(angle));
	rMat[1] = vec3(0., 1., 0.);
	rMat[2] = vec3(sin(angle), 0., cos(angle));
	return rMat * p;
}

vec3 rotateZ(vec3 p, float angle)
{
	mat3x3 rMat;
	rMat[0] = vec3(cos(angle), sin(angle), 0.);
	rMat[1] = vec3(-sin(angle), cos(angle), 0.);
	rMat[2] = vec3(0., 0., 1.);
	return rMat * p;
}

#endif