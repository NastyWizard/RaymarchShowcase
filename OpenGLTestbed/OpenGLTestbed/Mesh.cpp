#include "Mesh.h"
#include "MeshPrimitives.h"

Mesh::Mesh()
{
	// generate buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);
}

Mesh::~Mesh()
{
}

void Mesh::Init()
{
	// bind buffer
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// buffer data

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// normal array

	// unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::SetMesh(Primitive type)
{
	switch (type)
	{
	case Mesh::NONE:
		if (vertices != nullptr)
			delete vertices;
		if (indices != nullptr)
			delete indices;

		vertices = new float[0];
		indices = new unsigned int[0];
		break;
	case Mesh::RECT:
		MeshPrimitives::Create2DRect(1,1,)
		break;
	case Mesh::CIRCLE:
		break;
	case Mesh::CUBE:
		break;
	default:
		break;
	}
}

void Mesh::LoadMesh(std::string loc)
{
}

void Mesh::Draw()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
