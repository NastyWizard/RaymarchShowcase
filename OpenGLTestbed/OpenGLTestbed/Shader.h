#pragma once
#include "Helpers.h"
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
	// functions
public:
	Shader() {}
	Shader(std::string vert, std::string frag) { Initialize(vert, frag); }
	~Shader() {}

	void Initialize(std::string vert, std::string frag);
	void UseShader();
	unsigned int GetShader() { return shaderProgram; }

private:

};


void Shader::Initialize(std::string vert, std::string frag)
{

	// create shaders
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	// VERTEX
	
	// load the shader code

	char* vertShaderRaw[1];

	LoadFile(vert, vertShaderRaw[0]);

	glShaderSource(vertexShader, 1, vertShaderRaw, nullptr);
	glCompileShader(vertexShader);

	// check for errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// FRAGMENT

	// load the shader code

	char* fragShaderRaw[1];

	LoadFile(frag, fragShaderRaw[0]);

	glShaderSource(fragmentShader, 1, fragShaderRaw, nullptr);
	glCompileShader(fragmentShader);


	int successFrag;
	char infoLogFrag[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFrag);

	if (!successFrag)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLogFrag);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLogFrag << std::endl;
	}

	// link the shader to the program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int successLink;
	char infoLogLink[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successLink);
	if (!successLink) 
	{
		glGetShaderInfoLog(shaderProgram, 512, nullptr, infoLogLink);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLogLink << std::endl;
	}

	// clear shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::UseShader()
{
	glUseProgram(shaderProgram);
}