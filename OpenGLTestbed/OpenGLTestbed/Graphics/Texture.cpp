#include "Texture.h"
//#include "stb_image.h"
#include "..\Libraries\lodepng\lodepng.h"
#include "..\Util\Helpers.h"


Texture::Texture(std::string loc, GLint minFilter, GLint magFilter)
{
	LoadTexture(loc.c_str(), minFilter, magFilter);
	location = loc;
}

Texture::Texture()
{
}

Texture::~Texture()
{
}

void Texture::LoadTexture(const char* filename, GLint minFilter, GLint magFilter)
{
	unsigned int width, height;
	long filesize;
	unsigned char* filebuffer;
	LoadFile(filename, filebuffer, filesize);

	std::vector<unsigned char> pngbuffer;

	//std::vector<unsigned char> png;
	//
	//lodepng::load_file(png, filename);

	unsigned int result = lodepng::decode(pngbuffer, width, height, filename);// lodepng_decode32(&pngbuffer, &width, &height, filebuffer, filesize);
	
	if (result)
	{
		std::cout << result << std::endl;
		return;
	}
	//assert(result == 0);

	//std::cout << &pngbuffer[0] << std::endl;
	//FlipImageVertically(pngbuffer, width, height);

	GLuint texhandle = 0;
	glGenTextures(1, &texhandle);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texhandle);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pngbuffer[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	glTex = texhandle;
	CheckForGLErrors();
}

void Texture::FlipImageVertically(std::vector<unsigned char> &buffer, unsigned int WIDTH, unsigned int HEIGHT)
{
	// temp allocation big enough for one line
	unsigned int* temp;
	temp = new unsigned int[WIDTH];
	int linesize = WIDTH * 4;

	for (unsigned int y = 0; y<HEIGHT / 2; y++)
	{
		int LineOffsetY = y * WIDTH;
		int LineOffsetHminusY = (HEIGHT - 1 - y)*WIDTH;

		memcpy(temp, &buffer[LineOffsetY], linesize);
		memcpy(&buffer[LineOffsetY], &buffer[LineOffsetHminusY], linesize);
		memcpy(&buffer[LineOffsetHminusY], temp, linesize);
	}

	delete temp;
}