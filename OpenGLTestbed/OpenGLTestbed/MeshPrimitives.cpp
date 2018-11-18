#include "MeshPrimitives.h"

void MeshPrimitives::Create2DRect(float width, float height, float *&vertArray, unsigned int *&indexArray)
{
	//  x        y       z
	float vertices[] =
	{
		width/2.0f,		height/2.0f,	.0f, // top right
		width / 2.0f,	-height/2.0f,	.0f, // bottom right
		-width / 2.0f,	-height/2.0f,	.0f, // bottom left
		-width / 2.0f,	height/2.0f,	.0f // top left
	};

	unsigned int indices[] =
	{
		0,1,3,
		1,2,3
	};

	vertArray = vertices;
	indexArray = indices;
}
