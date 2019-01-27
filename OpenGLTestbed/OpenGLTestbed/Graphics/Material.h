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
	enum UniformType
	{
		SAMPLER, MAT4X4, INT, FLOAT, FLOAT2, FLOAT3, FLOAT4
	};


	// uniform maps
	std::map<std::string, Texture*> texUnfs;

	std::map<std::string, mat4x4> mat4x4Unfs;

	std::map<std::string, float> floatUnfs;
	std::map<std::string, float2> float2Unfs;
	std::map<std::string, float3> float3Unfs;
	std::map<std::string, float4> float4Unfs;

	std::map<std::string, int> intUnfs;

	//functions
public:
	Material(Shader* shdr) { SetShader(shdr); }
	Material();
	~Material();

	void SetShader(Shader* shdr);
	Shader* GetShader();
	void UseShader();
	void UpdateGlobalUniforms();
	void UpdateUniqueUniforms();

	// uniform adding, use these for the material to handle updating of uniforms

	void AddUniformSampler2D(std::string loc, Texture* tex);

	void AddUniformMatrix4x4(std::string loc, mat4x4 matrix);
	void AddUniformInt(std::string loc, int n);

	void AddUniformFloat(std::string loc, float n);

	void AddUniformFloat2(std::string loc, float x, float y);
	void AddUniformFloat3(std::string loc, float x, float y, float z);
	void AddUniformFloat4(std::string loc, float x, float y, float z, float w);

	void AddUniformFloat2(std::string loc, float2 v) { AddUniformFloat2(loc, v.x, v.y); }
	void AddUniformFloat3(std::string loc, float3 v) { AddUniformFloat3(loc, v.x, v.y, v.z); }
	void AddUniformFloat4(std::string loc, float4 v) { AddUniformFloat4(loc, v.x, v.y, v.z, v.w); }

	// change uniforms stored in maps, could honestly get rid of the 'Add' functions and merge functionality with 'Set', but frig it.
	void SetUniformSampler2D(std::string loc, Texture* tex);
		 
	void SetUniformMatrix4x4(std::string loc, mat4x4 matrix);
	void SetUniformInt(std::string loc, int n);
		 
	void SetUniformFloat(std::string loc, float n);
		 
	void SetUniformFloat2(std::string loc, float x, float y);
	void SetUniformFloat3(std::string loc, float x, float y, float z);
	void SetUniformFloat4(std::string loc, float x, float y, float z, float w);
		 
	void SetUniformFloat2(std::string loc, float2 v) { SetUniformFloat2(loc, v.x, v.y); }
	void SetUniformFloat3(std::string loc, float3 v) { SetUniformFloat3(loc, v.x, v.y, v.z); }
	void SetUniformFloat4(std::string loc, float4 v) { SetUniformFloat4(loc, v.x, v.y, v.z, v.w); }

	// uniform force setting

	void ApplyUniformSampler2D(std::string loc, Texture* tex);
	void ApplyUniformSampler2D_s(unsigned int id, std::string loc, Texture* tex);

	void ApplyUniformMatrix4x4(std::string loc, mat4x4 matrix);
	void ApplyUniformInt(std::string loc, int n);

	void ApplyUniformFloat(std::string loc, float n);

	void ApplyUniformFloat2(std::string loc, float x, float y);
	void ApplyUniformFloat3(std::string loc, float x, float y, float z);
	void ApplyUniformFloat4(std::string loc, float x, float y, float z, float w);

	void ApplyUniformFloat2(std::string loc, float2 v);
	void ApplyUniformFloat3(std::string loc, float3 v);
	void ApplyUniformFloat4(std::string loc, float4 v);
private:

	// uniforms

	void UpdateUniformSampler2D();
		 
	void UpdateUniformMatrix4x4();
	void UpdateUniformInt();
		 
	void UpdateUniformFloat();
	void UpdateUniformFloat2();
	void UpdateUniformFloat3();
	void UpdateUniformFloat4();
};