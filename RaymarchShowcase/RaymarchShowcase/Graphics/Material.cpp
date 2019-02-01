#include "Material.h"
#include "..\Util\Time.h"
#include "..\Util\Window.h"

Material::Material()
{
	shader = nullptr;
}

Material::~Material()
{
	if (shader != nullptr) 
	{
		delete shader;
		shader = nullptr;
	}
}

void Material::SetShader(Shader* shdr)
{
	if (shader != nullptr)
	{
		delete shader;
		shader = nullptr;
	}
	shader = shdr;
}


Shader* Material::GetShader()
{
	return shader;
}

void Material::UseShader()
{
	if (shader != nullptr)shader->UseShader();
}

// UNIFORMS ---------------

void Material::UpdateGlobalUniforms()
{
	//TODO: look into putting this stuff in a UBO
	ApplyUniformFloat("time", Time::GetTime());
	ApplyUniformFloat2("resolution", (float)Window::width, (float)Window::height);
	texCount = 0;
}

void Material::UpdateUniqueUniforms()
{

	if (texUnfs.size() > 0)
		UpdateUniformSampler2D();

	if (mat4x4Unfs.size() > 0)
		UpdateUniformMatrix4x4();

	if (intUnfs.size() > 0)
		UpdateUniformInt();

	if (floatUnfs.size() > 0)
		UpdateUniformFloat();

	if (float2Unfs.size() > 0)
		UpdateUniformFloat2();

	if (float3Unfs.size() > 0)
		UpdateUniformFloat3();

	if (float4Unfs.size() > 0)
		UpdateUniformFloat4();
}

void Material::AddUniformSampler2D(std::string loc, Texture * tex)
{
	if (texUnfs.find(loc) == texUnfs.end())
		texUnfs.insert(std::make_pair(loc, tex));

	if (Uniforms.find(loc) == Uniforms.end())
		Uniforms.insert(std::make_pair(loc, UniformType::SAMPLER2D));
}

void Material::AddUniformMatrix4x4(std::string loc, mat4x4 matrix)
{
	
	if (mat4x4Unfs.find(loc) == mat4x4Unfs.end())
		mat4x4Unfs.insert(std::make_pair(loc, matrix));
	if (Uniforms.find(loc) == Uniforms.end())
		Uniforms.insert(std::make_pair(loc, UniformType::MAT4X4));
}

void Material::AddUniformInt(std::string loc, int n)
{
	if (intUnfs.find(loc) == intUnfs.end())
		intUnfs.insert(std::make_pair(loc, n));
	if (Uniforms.find(loc) == Uniforms.end())
		Uniforms.insert(std::make_pair(loc, UniformType::INT));
}

void Material::AddUniformFloat(std::string loc, float n)
{
	if (floatUnfs.find(loc) == floatUnfs.end())
		floatUnfs.insert(std::make_pair(loc, n));
	if (Uniforms.find(loc) == Uniforms.end())
		Uniforms.insert(std::make_pair(loc, UniformType::FLOAT));
}

void Material::AddUniformFloat2(std::string loc, float x, float y)
{
	if (float2Unfs.find(loc) == float2Unfs.end())
		float2Unfs.insert(std::make_pair(loc, float2(x,y)));
	if (Uniforms.find(loc) == Uniforms.end())
		Uniforms.insert(std::make_pair(loc, UniformType::FLOAT2));
}

void Material::AddUniformFloat3(std::string loc, float x, float y, float z)
{
	if (float3Unfs.find(loc) == float3Unfs.end())
		float3Unfs.insert(std::make_pair(loc, float3(x,y,z)));
	if (Uniforms.find(loc) == Uniforms.end())
		Uniforms.insert(std::make_pair(loc, UniformType::FLOAT3));
}

void Material::AddUniformFloat4(std::string loc, float x, float y, float z, float w)
{
	if (float4Unfs.find(loc) == float4Unfs.end())
		float4Unfs.insert(std::make_pair(loc, float4(x,y,z,w)));
	if (Uniforms.find(loc) == Uniforms.end())
		Uniforms.insert(std::make_pair(loc, UniformType::FLOAT4));
}

void Material::AddUniformColor(std::string loc, float r, float g, float b, float a)
{
	if (float4Unfs.find(loc) == float4Unfs.end())
		float4Unfs.insert(std::make_pair(loc, float4(r, g, b, a)));
	if (Uniforms.find(loc) == Uniforms.end())
		Uniforms.insert(std::make_pair(loc, UniformType::COLOR));
}

void Material::SetUniformSampler2D(std::string loc, Texture * tex)
{
	if (float4Unfs.find(loc) == float4Unfs.end())
	{
		AddUniformSampler2D(loc, tex);
		return;
	}
	texUnfs.at(loc) = tex;
}

void Material::SetUniformMatrix4x4(std::string loc, mat4x4 matrix)
{
	if (mat4x4Unfs.find(loc) == mat4x4Unfs.end())
	{
		AddUniformMatrix4x4(loc, matrix);
		return;
	}
	mat4x4Unfs.at(loc) = matrix;
}

void Material::SetUniformInt(std::string loc, int n)
{
	if (intUnfs.find(loc) == intUnfs.end())
	{
		AddUniformInt(loc, n);
		return;
	}
	intUnfs.at(loc) = n;
}

void Material::SetUniformFloat(std::string loc, float n)
{
	if (floatUnfs.find(loc) == floatUnfs.end())
	{
		AddUniformFloat(loc, n);
		return;
	}
	floatUnfs.at(loc) = n;
}

void Material::SetUniformFloat2(std::string loc, float x, float y)
{
	if (float2Unfs.find(loc) == float2Unfs.end())
	{
		AddUniformFloat2(loc, x, y);
		return;
	}
	float2Unfs.at(loc) = float2(x, y);
}

void Material::SetUniformFloat3(std::string loc, float x, float y, float z)
{
	if (float3Unfs.find(loc) == float3Unfs.end())
	{
		AddUniformFloat3(loc, x, y, z);
		return;
	}
	float3Unfs.at(loc) = float3(x, y, z);
}

void Material::SetUniformFloat4(std::string loc, float x, float y, float z, float w)
{
	if (float4Unfs.find(loc) == float4Unfs.end())
	{
		AddUniformFloat4(loc, x, y, z, w);
		return;
	}
	float4Unfs.at(loc) = float4(x, y, z, w);
}

void Material::SetUniformColor(std::string loc, float r, float g, float b, float a)
{
	if (float4Unfs.find(loc) == float4Unfs.end())
	{
		AddUniformColor(loc, r, g, b, a);
		return;
	}
	float4Unfs.at(loc) = float4(r, g, b, a);
}


void Material::ApplyUniformSampler2D(std::string loc, Texture* tex)
{
	if (texCount >= 32) 
	{
		std::cout << "ERROR: Tex ID > 31 on Material '" << Name.c_str() << "'/n";
		return;
	}

	glActiveTexture(GL_TEXTURE0 + texCount);
	glBindTexture(GL_TEXTURE_2D, tex->GetTexture());

	ApplyUniformInt(loc, texCount++);
	//SetUniformInt(loc, tex->GetTexture());
}

// specific ID version of SetUniformSampler2D
void Material::ApplyUniformSampler2D_s(unsigned int id, std::string loc, Texture* tex)
{

	if (id >= 32)
	{
		std::cout << "ERROR: Tex ID > 31 on Material '" << Name.c_str() << "'/n";
		return;
	}

	glActiveTexture(GL_TEXTURE0 + id);
	glBindTexture(GL_TEXTURE_2D, tex->GetTexture());

	ApplyUniformInt(loc, id);
}

void Material::ApplyUniformMatrix4x4(std::string loc, mat4x4 matrix)
{
	int glLoc = glGetUniformLocation(shader->GetShader(), loc.c_str());
	glUniformMatrix4fv(glLoc, 1, GL_FALSE, matrix.matrix); // GL_FALSE = ROW MAJOR
}

void Material::ApplyUniformInt(std::string loc, int n)
{
	int glLoc = glGetUniformLocation(shader->GetShader(), loc.c_str());
	glUniform1i(glLoc, n);
}

void Material::ApplyUniformFloat(std::string loc, float n)
{
	int glLoc = glGetUniformLocation(shader->GetShader(), loc.c_str());
	glUniform1f(glLoc, n);
}

void Material::ApplyUniformFloat2(std::string loc, float x, float y)
{
	int glLoc = glGetUniformLocation(shader->GetShader(), loc.c_str());
	glUniform2f(glLoc, x, y);
}

void Material::ApplyUniformFloat3(std::string loc, float x, float y, float z)
{
	int glLoc = glGetUniformLocation(shader->GetShader(), loc.c_str());
	glUniform3f(glLoc, x, y, z);
}

void Material::ApplyUniformFloat4(std::string loc, float x, float y, float z, float w)
{
	int glLoc = glGetUniformLocation(shader->GetShader(), loc.c_str());
	glUniform4f(glLoc, x, y, z, w);
}

void Material::ApplyUniformFloat2(std::string loc, vec2 v)
{
	int glLoc = glGetUniformLocation(shader->GetShader(), loc.c_str());
	glUniform2f(glLoc, v.x, v.y);
}

void Material::ApplyUniformFloat3(std::string loc, vec3 v)
{
	int glLoc = glGetUniformLocation(shader->GetShader(), loc.c_str());
	glUniform3f(glLoc, v.x, v.y, v.z);
}

void Material::ApplyUniformFloat4(std::string loc, vec4 v)
{
	int glLoc = glGetUniformLocation(shader->GetShader(), loc.c_str());
	glUniform4f(glLoc, v.x, v.y, v.z, v.w);
}

void Material::UpdateUniformSampler2D()
{
	std::map<std::string, Texture*>::iterator it = texUnfs.begin();

	while (it != texUnfs.end())
	{
		std::string loc = it->first;
		Texture* value = it->second;
		
		ApplyUniformSampler2D(loc, value);

		it++;
	}
}

void Material::UpdateUniformMatrix4x4()
{
	std::map<std::string, Matrix4x4>::iterator it = mat4x4Unfs.begin();

	while (it != mat4x4Unfs.end())
	{
		std::string loc = it->first;
		Matrix4x4 value = it->second;

		ApplyUniformMatrix4x4(loc, value);

		it++;
	}
}

void Material::UpdateUniformInt()
{
	std::map<std::string, int>::iterator it = intUnfs.begin();

	while (it != intUnfs.end())
	{
		std::string loc = it->first;
		int value = it->second;

		ApplyUniformInt(loc, value);

		it++;
	}
}

void Material::UpdateUniformFloat()
{
	std::map<std::string, float>::iterator it = floatUnfs.begin();

	while (it != floatUnfs.end())
	{
		std::string loc = it->first;
		float value = it->second;

		ApplyUniformFloat(loc, value);

		it++;
	}
}

void Material::UpdateUniformFloat2()
{
	std::map<std::string, float2>::iterator it = float2Unfs.begin();

	while (it != float2Unfs.end())
	{
		std::string loc = it->first;
		float2 value = it->second;

		ApplyUniformFloat2(loc, value);

		it++;
	}
}

void Material::UpdateUniformFloat3()
{
	std::map<std::string, float3>::iterator it = float3Unfs.begin();

	while (it != float3Unfs.end())
	{
		std::string loc = it->first;
		float3 value = it->second;

		ApplyUniformFloat3(loc, value);

		it++;
	}
}

void Material::UpdateUniformFloat4()
{
	std::map<std::string, float4>::iterator it = float4Unfs.begin();

	while (it != float4Unfs.end())
	{
		std::string loc = it->first;
		float4 value = it->second;

		ApplyUniformFloat4(loc, value);

		it++;
	}
}
