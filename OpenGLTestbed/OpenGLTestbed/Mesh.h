#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>

class Mesh 
{
	// variables
public:
	enum Primitive
	{
		NONE, RECT, CIRCLE, CUBE
	};
private:
	unsigned int VBO;
	unsigned int VAO;
	unsigned int IBO;
	float* vertices;
	unsigned int* indices;

	// functions
public:
	Mesh();
	~Mesh();

	void Init();

	void SetMesh(Primitive type);
	void LoadMesh(std::string loc);

	void Draw();
private:

};