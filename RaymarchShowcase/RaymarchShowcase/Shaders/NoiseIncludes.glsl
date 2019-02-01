
#ifndef _NOISE_INCLUDES_
#define _NOISE_INCLUDES_

float Random(vec2 v){ return(fract(sin(dot(v, vec2(89.1843,26.8526)))*56881.168487)); }



float NoiseTexture2d(vec3 p, sampler2D img)
{
	vec3 i = floor(p);
	vec3 f = fract(p);
	
	// interpolation
    vec3 u = f*f*f*(f*(f*6.-15.)+10.);

	vec2 uv = (p.xy + vec2(37.,17.)*p.z) + f.xy;
	vec2 rg = texture(img, (uv + .5) / 256.).yx;

	return -1. + 2. * mix(rg.x,rg.y,f.z);

}

float Noise(vec2 uv)
{
    vec2 i = floor(uv);
    vec2 f = fract(uv);
    
    float bl = Random(i);
    float br = Random(i + vec2(1.0,0.0));
    float tl = Random(i + vec2(0.0,1.0));
    float tr = Random(i + vec2(1.0,1.0));
    
    // cubic
    vec2 u = f * f * (3. - 2. * f); 
    
    // quintic
    u = f*f*f*(f*(f*6.-15.)+10.);
    
    return mix(bl,br,u.x)+
        	(tl - bl) * u.y * (1.0-u.x) +
        	(tr - br) * u.x * u.y;
}

float FBMNoise(vec2 uv, int octaves)
{
	float value = 0.0;
	float amp = .5;
	float freq = 0.;

	for(int i = 0; i < octaves; i++)
	{
		value += amp * Noise(uv);
		uv *= 2.;
		amp *= .5;
	}
	return value;

}

#endif