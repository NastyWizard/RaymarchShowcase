#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

varying vec3 vPos;
varying vec2 vTexCoord;

uniform float time;
uniform mat4x4 ObjectMatrix;

void main()
{
	vPos = aPos;
	vTexCoord = aTexCoord;
	vec4 pos = ObjectMatrix * vec4(aPos,1.0f);
	gl_Position = pos;
}