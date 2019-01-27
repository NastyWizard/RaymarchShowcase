#ifndef _SDF_INCLUDES_
#define _SDF_INCLUDES_
// Signed distance fields includes, for raymarching

// primitives
float sdSphere(vec3 p, float r)
{
	return length(p) - r;
}

float sdPlane(vec3 p, vec3 n)
{
	n = normalize(n);
	return dot(p, n.xyz)+1.;
}

// operations

vec3 opRep(vec3 p, vec3 r)
{
	return mod(abs(p),r) - .5 * r;
}

vec3 opRepXZ(vec3 p, vec3 r)
{
	vec3 res = mod(abs(p),r) - .5 * r;
	res.y = p.y;
	return res;
}
#endif 