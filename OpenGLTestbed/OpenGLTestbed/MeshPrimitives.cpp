#include "MeshPrimitives.h"

void MeshPrimitives::Create2DRect(float width, float height, std::vector<float> &vertArray, std::vector<unsigned int> &indexArray)
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

	vertArray.clear();
	indexArray.clear();

	for (int i = 0; i < 12; i++)
		vertArray.push_back(vertices[i]);

	for (int i = 0; i < 6; i++)
		indexArray.push_back(indices[i]);

}
