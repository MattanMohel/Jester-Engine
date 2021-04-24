#pragma once

#include <GL/glew.h>
#include "RendererBase.h"

#define SCALE 500.0f

enum class RenderMode
{
	POINTS         = 0,
	LINES          = 1,
	LINE_LOOP      = 2,
	LINE_STRIP     = 3,
	TRIANGLES      = 4,
	TRIANGLE_STRIP = 5,
	TRIANGLE_FAN   = 6,
};

class Mesh
{
public:
	Mesh(const RenderMode& renderMode);
	~Mesh();

	void CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int verticesCount, unsigned int indicesCount);
	void ClearMesh();
	void Draw();

private:
	RenderMode m_RenderMode; 

	GLuint VAO;
	GLsizei m_IndexCount;
};

