#version 330 core

#define MAXSTEPS 1024
#define MAXDIST 200.

#include "Shaders/DefaultIncludes.glsl"
#include "Shaders/NoiseIncludes.glsl"
#include "Shaders/SDFIncludes.glsl"

out vec4 FragColor;

varying vec3 vPos;
varying vec2 vTexCoord;

uniform sampler2D MainTex;
uniform sampler2D MainTex2;
uniform mat4x4 ObjectMatrix;

uniform	float MinFogDist;
uniform float MaxFogDist;
uniform float NoiseYBoost;

uniform vec3 CameraPos;
uniform vec4 SphereColor;
uniform vec4 GroundColor;
uniform vec4 FogColor;
uniform vec2 NoiseScale;
uniform int MaxSteps;
uniform int Debug;


vec2 map(vec3 p)
{


	// SCREW AND GEAR
	vec3 gp = p;
	gp.y = mod(gp.y, .6) - .3;
	gp.y = min(gp.y, 4.);

	if(mod(floor(p.y / .6), 2.) == 0.)
	{
		gp = rotateY(gp,time * .25);
	}
	else
	{
		gp = rotateY(gp,-time * .5);
	}

	float screw = sdScrew(p,vec2(1.,4.));

	float gear = sdGear(gp);
	gear = OpS(sdPlane(vec3(0.,2.,0.)-p,vec3(0,1.,0.)),gear);
	
	vec2 res = OpU2(vec2(screw,3.), vec2(gear, 4.)); 

	// SPONGE
	vec3 sp = vec3(0.,4.5,0.) - p;

	float sponge = sdMengerSponge(rotateZ(rotateY(sp, time*.15),-time * .5),rotateX(sp,time * .6) + time * .25);
	vec2 sSponge = vec2(OpI(sponge,sdSphere(sp,1.)),2.);
	
	res = OpU2(res, sSponge);
	
	sp.x -= sin(time) * 4.;
	sp.z -= cos(time) * 4.;

	float spongeOrbit = sdMengerSponge(rotateZ(rotateY(sp, time*.15),-time * .5),rotateX(sp,time * .6) + time * .25);
	sSponge = vec2(OpI(spongeOrbit,sdSphere(sp,1.)),2.);
	
	res = OpU2(res, sSponge);

	// END
	float plane = sdPlane(p,vec3(0.,1.,0.));
	return OpU2(res, vec2(plane, 1.0));
}

vec3 calcNormal(in vec3 p)
{
    const float eps = 0.0001;
    const vec2 h = vec2(eps,0);
    return normalize( vec3(map(p+h.xyy).x - map(p-h.xyy).x,
                           map(p+h.yxy).x - map(p-h.yxy).x,
                           map(p+h.yyx).x - map(p-h.yyx).x ) );
}

// soft shadow function by iq
//http://www.iquilezles.org/www/articles/rmshadows/rmshadows.htm
float softshadow( in vec3 ro, in vec3 rd, float mint, float maxt, float k )
{
    float res = 1.0;
    float ph = 1e20;
    for( float t=mint; t < maxt; )
    {
        float h = map(ro + rd*t).x;
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
        float d = map(p + h*n).x;
        occ += (h-d)*sca;
        sca *= .95;
    }
    return clamp(1. - 1.5 * occ, 0.1, 1.);
}

void main()
{
	
	vec2 texCoord = vTexCoord;
	texCoord.y = 1.-texCoord.y;

	vec2 fragCoord = texCoord * resolution;
	
	// set up camera
    vec2 sp =  (2.0*fragCoord.xy-resolution.xy) / resolution.y;
    vec3 ro = CameraPos;
    vec3 rd = normalize(vec3(sp,-2.));
	//rd = rotateY(rd, (sin(time * .5) + sin(time * .25)) * (PI * .5));
    //
	
    vec3 lightDir = normalize(vec3(sin(time),sin(time*2.)*.5 + .75,cos(time)));

    vec3 col = vec3(0.3,0.5,0.8);
   	
    // sun
    vec3 sun = vec3(pow(max(dot(rd,lightDir),0.),60.));
	
	// fog stuff
	
	float fogPow = 1.f;
	float fogScale = 1.f;
	float fog = 0.;

	//
    
    float t = 0.001;
    
    for(int i = 0; i < MaxSteps; i++)
    {
    	vec3 p = ro + rd * t;
		vec2 m = map(p);
        float d = m.x;
		
		fog = smoothstep(MinFogDist, MaxFogDist, distance(p, ro));
		fog = pow(fog, fogPow) * fogScale;

        if(t > MaxFogDist) break;
        
        // draw
        if(d < 0.001)
        {
            vec3 n = calcNormal(p);
            float NDotL = dot(n,lightDir);
            float iNDotL = dot(n,-lightDir);
            NDotL = max(NDotL,0.1);
            float shadow = softshadow(p,lightDir,.1,4.,16.)+.1;
			shadow = clamp(shadow,.5,1.);

            // fresnel
            float NDotV = dot(n, rd); 
            float fscale= 2.;
            float fpow  =2.;
            float fbump = -.5;
            float f = 1.-pow(NDotV,fpow) * fscale;
            f = max(f+fbump,0.);
            
            float occ = calcAO(p,n);
            
        	col = vec3(NDotL+.5) * shadow * occ;
			col += f * occ;

			// plane material
			if(m.y == 1.)
				col *= GroundColor.xyz;
			else if(m.y == 2.)
				col *= SphereColor.xyz;
			else if(m.y == 3.)
				col *= vec3(.45,.45,.5);
			else if(m.y == 4.)
				col *= vec3(.67,.65,.4);

			// -------- debug renders --------

			// normal render
			if(Debug == 1)
				col = n;
			
			// depth render in relation to fog edge
			if(Debug == 2)
				col = vec3(distance(p,ro)) / MaxFogDist;
			
			// Number of steps to draw the pixel, full red = max steps, black = very few steps
			if(Debug == 3)
				col = vec3(float(i) / float(MaxSteps), 0., 0.);

			// -------- debug renders --------

            break;
        }
        
        t += d;
    }
    // Output to screen
    FragColor = vec4(mix(col, FogColor.rgb, fog) + sun, 1.0);
}