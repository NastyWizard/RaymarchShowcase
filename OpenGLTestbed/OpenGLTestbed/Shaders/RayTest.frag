#version 330 core

#define MAXSTEPS 1024
#define MAXDIST 200.
#define PI 3.14159265359

#include "Shaders/NoiseIncludes.glsl"
#include "Shaders/SDFIncludes.glsl"

out vec4 FragColor;

varying vec3 vPos;
varying vec2 vTexCoord;

uniform float time;
uniform vec2 resolution;
uniform sampler2D MainTex;
uniform sampler2D MainTex2;
uniform mat4x4 ObjectMatrix;

uniform vec3 SpherePos;
uniform vec4 SphereColor;
uniform vec4 GroundColor;
uniform vec2 NoiseScale;
uniform int MaxSteps;

float map(vec3 p)
{
	return min(sdSphere(opRepXZ((Noise(p.xz * NoiseScale) * SpherePos)-p, vec3(10., 0. ,10.)),1.0),sdPlane(vec3(0.,Noise(p.xz * NoiseScale),0.)-p,vec3(0.,-1.,0.)));
	//return min(sdSphere(vec3(0.0,0.0,-10.0)-p,1.0),sdPlane(vec3(0.,0.,0.)-p,vec3(0.,-1.,0.)));
}

vec3 calcNormal(in vec3 p)
{
    const float eps = 0.0001;
    const vec2 h = vec2(eps,0);
    return normalize( vec3(map(p+h.xyy) - map(p-h.xyy),
                           map(p+h.yxy) - map(p-h.yxy),
                           map(p+h.yyx) - map(p-h.yyx) ) );
}

// soft shadow function by iq
//http://www.iquilezles.org/www/articles/rmshadows/rmshadows.htm
float softshadow( in vec3 ro, in vec3 rd, float mint, float maxt, float k )
{
    float res = 1.0;
    float ph = 1e20;
    for( float t=mint; t < maxt; )
    {
        float h = map(ro + rd*t);
        if( h<0.001 )
            return 0.0;
        float y = h*h/(2.0*ph);
        float d = sqrt(h*h-y*y);
        res = min( res, k*d/max(0.0,t-y) );
        ph = h;
        t += h;
    }
    return clamp(res,0.,1.);
}
//

// taken from https://www.shadertoy.com/view/lsKcDD
float calcAO(vec3 p, vec3 n)
{
	float occ = 0.;
    float sca = 1.;
    for(int i = 0; i < 5; i++)
    {
        float h = 0.00 + 0.15*float(i)/4.0;
        float d = map(p + h*n);
        occ += (h-d)*sca;
        sca *= .95;
    }
    return clamp(1. - 1.5 * occ, 0.1, 1.);
}

vec3 rotateY(vec3 p, float angle)
{
	mat3x3 rMat;
	rMat[0] = vec3(cos(angle), 0., -sin(angle));
	rMat[1] = vec3(0., 1., 0.);
	rMat[2] = vec3(sin(angle), 0., cos(angle));
	return rMat * p;
}

void main()
{
	
	vec2 texCoord = vTexCoord;
	texCoord.y = 1.-texCoord.y;

	vec2 fragCoord = texCoord * resolution;
	
	// set up camera
    vec2 sp =  (2.0*fragCoord.xy-resolution.xy) / resolution.y;
    vec3 ro = vec3(0.0,3.,0.0);
    vec3 rd = normalize(vec3(sp,-2.));
	rd = rotateY(rd, (sin(time * .5) + sin(time * .25)) * (PI * .5));
    //
	
    vec3 lightDir = normalize(vec3(sin(time),sin(time*2.)*.5 + .75,cos(time)));

    vec3 col = vec3(0.3,0.5,0.8);
   	
    // sun
    vec3 sun = vec3(pow(max(dot(rd,lightDir),0.),60.));
	
	// fog stuff
	
	float minFogDist = 40.f;
	float maxFogDist = 60.f;
	float fogPow = 1.f;
	float fogScale = 1.f;
	vec3 fogCol = vec3(0.3, 0.6, 0.9);
	float fog = 0.;

	//
    
    float t = 0.;
    
    for(int i = 0; i < MaxSteps; i++)
    {
    	vec3 p = ro + rd * t;
        float d = map(p);
		
		fog = smoothstep(minFogDist, maxFogDist, distance(p, ro));
		fog = pow(fog, fogPow) * fogScale;

        if(t > maxFogDist) break;
        
        // draw
        if(d < 0.001)
        {
            vec3 n = calcNormal(p);
            float NDotL = dot(n,lightDir);
            float iNDotL = dot(n,-lightDir);
            NDotL = max(NDotL,0.);
            float shadow = softshadow(p,lightDir,.1,4.,16.)+.1;
			shadow = clamp(shadow,.5,1.);

            // fresnel
            float NDotV = dot(n, rd); 
            float fscale= 2.;
            float fpow  =4.;
            float fbump = -.91;
            float f = 1.-pow(NDotV,fpow) * fscale;
            f = max(f+fbump,0.);
            
            float occ = calcAO(p,n);
            
        	col = vec3(NDotL+.5) * shadow * occ;
            col *= f+1.0 ;

			vec3 gc = GroundColor.xyz;

			gc *= Noise(p.xz * NoiseScale);

			// plane material
			if(p.y < -.99)
				col *= gc;
			else // sphere mat
				col *= SphereColor.xyz;

			// -------- debug renders --------

			// normal render
            //col = n;
			
			// depth render in relation to fog edge
			//col = vec3(distance(p,ro)) / maxFogDist;
			
			// -------- debug renders --------

            break;
        }
        
        t += d;
    }
    // Output to screen
    FragColor = vec4(mix(col, fogCol, fog) + sun, 1.0);
}