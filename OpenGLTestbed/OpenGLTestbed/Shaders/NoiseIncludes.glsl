
#ifndef _NOISE_INCLUDES_
#define _NOISE_INCLUDES_

float Random(vec2 v){ return(fract(sin(dot(v, vec2(89.1843,26.8526)))*56881.168487)); }

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

#endif