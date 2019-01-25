#pragma once

#include "Shader.h"
#include "..\Math\VectorMath.h"
#include "Texture.h"
#include "..\Math\MatrixMath.h"
#include <map>


class Material 
{
	// variables
public:
	std::string name;
private:
	Shader* shader;
	int texCount = 0;

	//functions
public:
	Material(Shader* shdr) { SetShader(shdr); }
	Material();
	~Material();

	void SetShader(Shader* shdr);
	void UseShader();
	void UpdateGlobalUniforms();

	// uniforms

	void SetUniformSampler2D(std::string loc, Texture* tex);
	void SetUniformSampler2D_s(unsigned int id, std::string loc, Texture* tex);

	void SetUniformMatrix4x4(std::string loc, mat4x4 matrix);
	void SetUniformInt(std::string loc, int n);

	void SetUniformFloat(std::string loc, float n);

	void SetUniformFloat2(std::string loc, float x, float y);
	void SetUniformFloat3(std::string loc, float x, float y, float z);
	void SetUniformFloat4(std::string loc, float x, float y, float z, float w);


	void SetUniformFloat2(std::string loc, vec2 v);
	void SetUniformFloat3(std::string loc, vec3 v);
	void SetUniformFloat4(std::string loc, vec4 v);
private:

};