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
