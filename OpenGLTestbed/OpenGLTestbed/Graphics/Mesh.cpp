#include "Mesh.h"
#include "MeshPrimitives.h"
#include <memory>

Mesh::Mesh()
{
	// generate buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
}

void Mesh::Init()
{
	// bind buffer
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// prepare data

	int size = vertices.size() + normals.size() + uvs.size();

	//std::unique_ptr<float[]> finalData(new float[size]);
	//float* finalData = new float[size];
	std::vector<float> finalData(size);

	for (int i = 0; i < (size/8); i ++) 
	{
		int index = i * 8;
		finalData[index + 0] = vertices[(i * 3) + 0];
		finalData[index + 1] = vertices[(i * 3) + 1];
		finalData[index + 2] = vertices[(i * 3) + 2];

		finalData[index + 3] = normals[(i * 3) + 0];
		finalData[index + 4] = normals[(i * 3) + 1];
		finalData[index + 5] = normals[(i * 3) + 2];

		finalData[index + 6] = uvs[(i * 2) + 0];
		finalData[index + 7] = uvs[(i * 2) + 1];
	}

	// buffer data

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, &finalData[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
	

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// uvs
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	// unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::SetMesh(Primitive type)
{
	switch (type)
	{
	case Mesh::NONE:
		break;
	case Mesh::RECT:
		MeshPrimitives::Create2DRect(2, 2, vertices, indices, uvs, normals);
		break;
	case Mesh::CIRCLE:
		break;
	case Mesh::CUBE:
		break;
	default:
		break;
	}

	Init();
}

void Mesh::LoadMesh(std::string loc)
{
	Init();
}

void Mesh::Draw()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
