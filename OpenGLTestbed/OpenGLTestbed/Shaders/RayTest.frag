#version 330 core

#define MAXSTEPS 512
#define MAXDIST 200.

out vec4 FragColor;

varying vec3 vPos;
varying vec2 vTexCoord;

uniform float time;
uniform sampler2D MainTex;
uniform sampler2D MainTex2;
uniform mat4x4 ObjectMatrix;


float sdSphere(vec3 p, float r)
{
	return length(p) - r;
}

float sdPlane(vec3 p, vec3 n)
{
	n = normalize(n);
	return dot(p, n.xyz)+1.;
}

vec3 opRep(vec3 p, vec3 r)
{
	return mod(abs(p),r) - .5 * r;
}

float map(vec3 p)
{
	//return sdSphere(opRep(vec3(0.0,2.0,0.0)-p, vec3(0.,0.,1.)),1.0);
	return min(sdSphere(vec3(0.0,0.0,-10.0)-p,1.0),sdPlane(vec3(0.,0.,0.)-p,vec3(0.,-1.,0.)));
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
    return res;
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

void main()
{
	vec2 resolution = vec2(800.,600.);
	
	vec2 texCoord = vTexCoord;
	texCoord.y = 1.-texCoord.y;

	vec2 fragCoord = texCoord * resolution;
	
	// set up camera
    vec2 sp =  (2.0*fragCoord.xy-resolution.xy) / resolution.y;
    vec3 ro = vec3(sin(time*.5)*2.,3.,4.);
    vec3 rd = normalize(vec3(sp,-2.));
    //
	
    vec3 lightDir = normalize(vec3(sin(time),sin(time*2.)*.5 + .75,cos(time)));

    vec3 col = vec3(0.3,0.5,0.8);
   	
    // sun
    col += vec3(pow(max(dot(rd,lightDir),0.),80.));
    
    float t = 0.;
    
    for(int i = 0; i < MAXSTEPS; i++)
    {
    	vec3 p = ro + rd * t;
        float d = map(p);
        
        if(t > MAXDIST) break;
        
        // draw
        if(d < 0.001)
        {
            vec3 n = calcNormal(p);
            float NDotL = dot(n,lightDir);
            float iNDotL = dot(n,-lightDir);
            NDotL = max(NDotL,0.);
           	iNDotL = max(iNDotL,0.);
            float shadow = softshadow(p,lightDir,.1,16.,16.)+.4;
            
            // fresnel
            float NDotV = dot(n, rd); 
            float fscale= 2.;
            float fpow  =2.;
            float fbump = -.7;
            float f = 1.-pow(NDotV,fpow) * fscale;
            f = max(f+fbump,0.);
            
            float occ = calcAO(p,n);
            
            
        	col = vec3(NDotL+.1) * shadow * occ;
            col += f *(shadow+.5);
            //col = n;
            break;
        }
        
        t += d;
    }
    // Output to screen
    FragColor = vec4(col,1.0);


	//FragColor = mix(texel,texel2,0.5);//vec4(vTexCoord,0.0f, 1.0f);
}