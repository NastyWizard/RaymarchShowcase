#include "Material.h"

Material::Material()
{
	shader = nullptr;
}

Material::~Material()
{
}

void Material::SetShader(Shader* shdr)
{
	shader = shdr;
}

void Material::UseShader()
{
	if (shader != nullptr)shader->UseShader();
}

void Material::UpdateUniforms()
{
}
