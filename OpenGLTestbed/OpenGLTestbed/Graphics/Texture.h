#pragma once
#include <iostream>
#include <vector>
#include <glad\glad.h>
#include <GLFW\glfw3.h>

class Texture 
{
	// variables
private:
	std::string location;
	unsigned int glTex;
	int width, height;
	int numChannels;
public:

	//functions
private:
	void FlipImageVertically(std::vector<unsigned char> &buffer, unsigned int WIDTH, unsigned int HEIGHT);
public:
	Texture(std::string loc, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR);
	Texture();
	~Texture();

	std::string GetLocation() { return location; }

	void LoadTexture(const char* filename, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR);
	unsigned int GetTexture() { return glTex; }
};