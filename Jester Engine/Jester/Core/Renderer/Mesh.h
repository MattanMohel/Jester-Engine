#pragma once

#include <GL/glew.h>
#include "rCommon.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	void CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int verticesCount, unsigned int indicesCount);
	void ClearMesh();
	void Draw();

private:
	GLuint VAO;
	GLsizei m_IndexCount;
};

