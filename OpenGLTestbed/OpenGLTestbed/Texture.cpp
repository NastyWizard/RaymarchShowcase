#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>

Texture::Texture(std::string loc)
{
	LoadTexture(loc);
}

Texture::Texture()
{
}

Texture::~Texture()
{
}

void Texture::LoadTexture(std::string loc)
{
	glGenTextures(1, &glTex);
	glBindTexture(GL_TEXTURE_2D, glTex);

	// wrap / filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//

	// load the texture
	unsigned char* data = stbi_load(loc.c_str(), &width, &height, &numChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "ERROR: Texture Load Failed: " << loc.c_str() << std::endl;
	
	stbi_image_free(data);
}
