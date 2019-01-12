#version 330 core
out vec4 FragColor;

varying vec3 vPos;
varying vec2 vTexCoord;

uniform float time;
uniform sampler2D MainTex;
uniform sampler2D MainTex2;

void main()
{
	vec2 texCoord = vTexCoord;

	vec4 texel = texture(MainTex, texCoord);
	vec4 texel2 = texture(MainTex2, texCoord);

	FragColor =  mix(texel,texel2,0.5);//vec4(vTexCoord,0.0f, 1.0f);
}