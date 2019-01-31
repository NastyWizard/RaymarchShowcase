#ifndef _SDF_INCLUDES_
#define _SDF_INCLUDES_

float maxcomp2(vec2 a) { return max(a.x,a.y); }

// Signed distance fields includes, for raymarching

// primitives
float sdSphere(vec3 p, float r)
{
	//float ran = Noise(p.xy * 3.);
	//
	//ran = clamp(ran,.15,1.);

	return length(p) - (r);
}

float sdPlane(vec3 p, vec3 n)
{
	n = normalize(n);
	return dot(p, n.xyz)+1.;
}

float sdBox(vec3 p, vec3 b)
{
	vec3 d = abs(p) - b;
	return length(max(d,0.));
}

float sdCross(vec3 p)
{
	float r  = sdBox(p.xyz, vec3(FLT_MAX, 1.0, 1.0));
	float r1 = sdBox(p.yzx, vec3(1.0, FLT_MAX, 1.0));
	float r2 = sdBox(p.zxy, vec3(1.0, 1.0, FLT_MAX));
	
	float d1 = maxcomp2(abs(p.xy));
	float d2 = maxcomp2(abs(p.yz));
	float d3 = maxcomp2(abs(p.zx));

	return min(d1, min(d2,d3)) - 1.0;
}

vec3 rotateY(vec3 p, float angle)
{
	mat3x3 rMat;
	rMat[0] = vec3(cos(angle), 0., -sin(angle));
	rMat[1] = vec3(0., 1., 0.);
	rMat[2] = vec3(sin(angle), 0., cos(angle));
	return rMat * p;
}

uniform int FractalIterations;

float sdFractalCross(vec3 p)
{
	float d = sdBox(p,vec3(1.0));

   float s = 1.0;
   for( int m=0; m<FractalIterations; m++ )
   {
      vec3 a = mod( p*s, 2.0 )-1.0;
      s *= 3.0;
      vec3 r = 1.0 - 3.0*abs(a);

      float c = sdCross(r)/s;
      d = max(d,-c);
   }
   return d;
}

float sdMengerSponge(vec3 p, vec3 p2)
{
	float d = sdBox(p,vec3(1.0));
	float s = 1.0;
	for( int m=0; m<FractalIterations; m++ )
	{
	   vec3 a = mod( p2*s, 2.0 )-1.0;
	   s *= 3.0;
	   vec3 r = 1.0 - 3.0*abs(a);

	   float c = sdCross(r)/s;
	   d = max(d,c);
	}
	return d;
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

vec2 OpU2(vec2 d, vec2 d2)
{
	return d.x < d2.x ? d : d2;
}

//

#endif 