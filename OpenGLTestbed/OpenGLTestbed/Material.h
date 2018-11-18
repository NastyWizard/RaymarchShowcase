#pragma once
#include "Shader.h"

class Material 
{
	// variables
public:

private:
	Shader* shader;
	//functions
public:
	Material(Shader* shdr) { SetShader(shdr); }
	Material();
	~Material();

	void SetShader(Shader* shdr);
private:

};