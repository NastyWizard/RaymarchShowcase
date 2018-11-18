#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <vector>

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
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

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