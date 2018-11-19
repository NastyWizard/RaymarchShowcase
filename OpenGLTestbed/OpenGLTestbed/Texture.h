#pragma once
#include <iostream>

class Texture 
{
	// variables
private:
	unsigned int glTex;
	int width, height;
	int numChannels;
public:

	//functions
private:
public:
	Texture(std::string loc);
	Texture();
	~Texture();

	void LoadTexture(std::string loc);
	unsigned int GetTexture() { return glTex; }
};