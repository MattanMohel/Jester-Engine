#include "Mesh.h"

Mesh::Mesh(const RenderMode& renderMode)
	: m_RenderMode(renderMode), VAO(0), m_IndexCount(0)
{}

Mesh::~Mesh()
{
	ClearMesh();
}

void Mesh::CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int verticesCount, unsigned int indicesCount)
{
	m_IndexCount = indicesCount;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indicesCount, indices, GL_STATIC_DRAW);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * verticesCount, vertices, GL_STATIC_DRAW);

	//positions coordinates
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTICES[0]) * 5, 0);
	glEnableVertexAttribArray(0);
	//texture coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VERTICES[0]) * 5, (void*)(sizeof(VERTICES[0]) * 3));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	glDeleteBuffers(1, &IBO);
	glDeleteBuffers(1, &VBO);
}

void Mesh::Draw()
{
	if (m_IndexCount == 0) return;
	glBindVertexArray(VAO);
	glDrawElements((GLenum)m_RenderMode, m_IndexCount, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}

void Mesh::ClearMesh()
{
	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	m_IndexCount = 0;
}


