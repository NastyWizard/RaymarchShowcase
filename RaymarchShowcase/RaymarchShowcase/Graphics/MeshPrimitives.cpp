#include "MeshPrimitives.h"

void MeshPrimitives::Create2DRect(float width, float height, std::vector<float> &vertArray, std::vector<unsigned int> &indexArray, std::vector<float> &uvArray, std::vector<float> &normalArray)
{
	//  x					y			 z
	float vertices[] =
	{
		width/2.0f,		height/2.0f,	.0f, // top right
		width / 2.0f,	-height/2.0f,	.0f, // bottom right
		-width / 2.0f,	-height/2.0f,	.0f, // bottom left
		-width / 2.0f,	height/2.0f,	.0f// top left
	};

	float uvs[] =
	{
		1.0f, 1.0f-1.0f,
		1.0f, 1.0f-0.0f,
		0.0f, 1.0f-0.0f,
		0.0f, 1.0f-1.0f
	};

	float normals[] = 
	{
		0.0f,	0.0f,	-1.0f,
		0.0f,	0.0f,	-1.0f,
		0.0f,	0.0f,	-1.0f,
		0.0f,	0.0f,	-1.0f,
	};

	unsigned int indices[] =
	{
		0,1,3,
		1,2,3
	};

	vertArray.clear();
	indexArray.clear();
	uvArray.clear();
	normalArray.clear();

	for (int i = 0; i < 12; i++)
	{
		vertArray.push_back(vertices[i]);
		normalArray.push_back(normals[i]);
	}


	for (int i = 0; i < 8; i++)
		uvArray.push_back(uvs[i]);

	for (int i = 0; i < 6; i++)
		indexArray.push_back(indices[i]);

}
