#include "Line.h"

#include "../Core/Color.h"
#include "Camera.h"
#include "Mesh.h"

#include <glm/glm.hpp>

Line::Line() 
	: m_Shader(VS_PATH, FCOLOR_PATH), 
	m_Mesh(RenderMode::LINE_LOOP), m_Color(1.0f, 1.0f, 1.0f, 1.0f),
	m_Camera(Object::FindComponent<Camera>())
{}

void Line::SetVertices(const std::vector<Vector2>& verts)
{
	m_Vertices = verts;
	UpdateMesh();
}

void Line::SetVertex(const Vector2& newVertex, size_t index)
{
	m_Vertices[index] = newVertex;
	UpdateMesh(); 
}

void Line::RemoveVertex(size_t index)
{
	if (m_Vertices.size() == 0)
		return;

	m_Vertices.erase(m_Vertices.begin() + index);
	UpdateMesh();
}

void Line::AddVertex(size_t index)
{
	if (m_Vertices.size() == 0)
		m_Vertices.push_back(Vector2::Zero);
	else
		m_Vertices.insert(m_Vertices.begin() + index, Vector2::Zero);
	
	UpdateMesh(); 
} 

void Line::UpdateMesh()
{
	float* vertices = new float[m_Vertices.size() * 5];
	unsigned int* indices = new unsigned int[m_Vertices.size()];
	for (size_t i = 0; i < m_Vertices.size(); i++)
	{
		indices[i] = i;

		vertices[i * 5 + 0] = m_Vertices[i].x;
		vertices[i * 5 + 1] = m_Vertices[i].y;
		vertices[i * 5 + 2] = 0;
		vertices[i * 5 + 3] = 0;
		vertices[i * 5 + 4] = 0;
	}

	m_Mesh.CreateMesh(vertices, indices, m_Vertices.size() * 5, m_Vertices.size());

	delete[] vertices, indices;
}

void Line::OnUpdate()
{
	m_Shader.Bind();

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(-object->transform.position.x * SCALE, object->transform.position.y * SCALE, 1));
	model = glm::rotate(model, object->transform.rotation * Deg2Rad, glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(object->transform.scale.x * SCALE, object->transform.scale.y * SCALE, 1));

	m_Shader.SetUniform<glm::mat4>("model", model);
	m_Shader.SetUniform<glm::vec4>("color", glm::vec4(m_Color.r, m_Color.g, m_Color.b, m_Color.a));
	m_Shader.SetUniform<glm::mat4>("projection", m_Camera->Projection());
	m_Shader.SetUniform<glm::mat4>("view", m_Camera->CalculateViewMatrix());

	m_Mesh.Draw();

	Shader::Unbind();
}