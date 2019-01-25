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
	shader = shdr;
}

void Material::UseShader()
{
	if (shader != nullptr)shader->UseShader();
}

// UNIFORMS ---------------

void Material::UpdateGlobalUniforms()
{
	SetUniformFloat("time", Time::GetTime());
	SetUniformFloat2("resolution", (float)Window::width, (float)Window::height);
	texCount = 0;
}


void Material::SetUniformSampler2D(std::string loc, Texture* tex)
{
	if (texCount >= 32) 
	{
		std::cout << "ERROR: Tex ID > 31 on Material '" << name.c_str() << "'/n";
		return;
	}

	glActiveTexture(GL_TEXTURE0 + texCount);
	glBindTexture(GL_TEXTURE_2D, tex->GetTexture());

	SetUniformInt(loc, texCount++);
	//SetUniformInt(loc, tex->GetTexture());
}

// specific ID version of SetUniformSampler2D
void Material::SetUniformSampler2D_s(unsigned int id, std::string loc, Texture* tex)
{

	if (id >= 32)
	{
		std::cout << "ERROR: Tex ID > 31 on Material '" << name.c_str() << "'/n";
		return;
	}

	glActiveTexture(GL_TEXTURE0 + id);
	glBindTexture(GL_TEXTURE_2D, tex->GetTexture());

	SetUniformInt(loc, id);
}

void Material::SetUniformMatrix4x4(std::string loc, mat4x4 matrix)
{
	int glLoc = glGetUniformLocation(shader->GetShader(), loc.c_str());
	glUniformMatrix4fv(glLoc, 1, GL_FALSE, matrix.matrix); // GL_FALSE = ROW MAJOR
}

void Material::SetUniformInt(std::string loc, int n)
{
	int glLoc = glGetUniformLocation(shader->GetShader(), loc.c_str());
	glUniform1i(glLoc, n);
}

void Material::SetUniformFloat(std::string loc, float n)
{
	int glLoc = glGetUniformLocation(shader->GetShader(), loc.c_str());
	glUniform1f(glLoc, n);
}

void Material::SetUniformFloat2(std::string loc, float x, float y)
{
	int glLoc = glGetUniformLocation(shader->GetShader(), loc.c_str());
	glUniform2f(glLoc, x, y);
}

void Material::SetUniformFloat3(std::string loc, float x, float y, float z)
{
	int glLoc = glGetUniformLocation(shader->GetShader(), loc.c_str());
	glUniform3f(glLoc, x, y, z);
}

void Material::SetUniformFloat4(std::string loc, float x, float y, float z, float w)
{
	int glLoc = glGetUniformLocation(shader->GetShader(), loc.c_str());
	glUniform4f(glLoc, x, y, z, w);
}

void Material::SetUniformFloat2(std::string loc, vec2 v)
{
	int glLoc = glGetUniformLocation(shader->GetShader(), loc.c_str());
	glUniform2f(glLoc, v.x, v.y);
}

void Material::SetUniformFloat3(std::string loc, vec3 v)
{
	int glLoc = glGetUniformLocation(shader->GetShader(), loc.c_str());
	glUniform3f(glLoc, v.x, v.y, v.z);
}

void Material::SetUniformFloat4(std::string loc, vec4 v)
{
	int glLoc = glGetUniformLocation(shader->GetShader(), loc.c_str());
	glUniform4f(glLoc, v.x, v.y, v.z, v.w);
}
