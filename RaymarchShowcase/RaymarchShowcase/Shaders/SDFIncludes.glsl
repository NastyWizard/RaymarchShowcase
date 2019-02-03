#ifndef _SDF_INCLUDES_
#define _SDF_INCLUDES_

// Signed distance fields includes, for raymarching

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

// union
float OpU(float d, float d2)
{
	return min(d,d2);
}

vec2 OpU2(vec2 d, vec2 d2)
{
	return d.x < d2.x ? d : d2;
}

// intersection
float OpI(float d, float d2)
{
	return max(d, d2);
}

// subtraction 
float OpS(float d, float d2)
{
	return max(-d,d2);
}

vec2 OpS2(vec2 d, vec2 d2)
{
	return -d.x > d2.x ? d : d2;
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

// primitives
float sdSphere(vec3 p, float r)
{
	return length(p) - (r);
}

float sdTorus(vec3 p, vec2 t)
{
	vec2 q = vec2(length(p.xz)-t.x,p.y);
	return length(q)-t.y;
}

float sdDisk(vec3 p, vec2 h)
{
	vec2 d = abs(vec2(length(p.xz),p.y)) - h;
	return min(max(d.x,d.y),0.0) + length(max(d,0.0));
}

float sdScrew(vec3 p, vec2 h)
{
	vec3 pr = p;
	pr.y = mod(pr.y, .6) - .3;
	float r = sdTorus(pr, vec2(h.x,.05));
	return OpS(r, sdDisk(p,h));
}

float sdGear(vec3 p)
{
	vec3 rp = sin(p) * .3;
	float n = OpS(sdDisk(rp, vec2(.3,1.)), sdDisk(p, vec2(2., .25)));
	return n;
}

float sdNut(vec3 p)
{
	vec3 rp = tan(p) * .1;//opRepXZ(p, vec3(1.,1.,1.));
	float n = OpS(sdDisk(rp, vec2(.3,1.)), sdDisk(p, vec2(2., .25)));
	return n;
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

float sdCylinder(vec3 p, vec3 c)
{
	return length(p.xz-c.xy)-c.z;
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

#endif 