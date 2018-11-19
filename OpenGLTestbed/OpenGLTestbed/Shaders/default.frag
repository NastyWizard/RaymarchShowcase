#version 330 core
out vec4 FragColor;
varying vec3 vPos;

uniform float time;

void main()
{
	FragColor =  vec4(sin(time)*vPos, 1.0f);
}