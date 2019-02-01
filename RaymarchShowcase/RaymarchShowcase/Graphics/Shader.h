#pragma once
#include "..\Util\Helpers.h"
#include "..\Math\VectorMath.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
class Shader
{
	// variables
public:

private:
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;

	std::string vert;
	std::string frag;
	// functions
public:
	Shader() {}
	Shader(std::string vert, std::string frag) { Initialize(vert, frag); }
	~Shader() {}

	void Initialize(std::string vert, std::string frag);
	void UseShader();
	unsigned int GetShader() { return shaderProgram; }


	std::string GetVertex();
	std::string GetFragment();

private:

	void HandleIncludes(char* in, char*& out);

	void checkCompileErrors(GLuint shader, std::string type);
};
