#include "Shape.h"

Shape::Shape()
	: m_Shader(VS_PATH, FCOLOR_PATH),
	m_Mesh(RenderMode::TRIANGLE_FAN), m_Color(1.0f, 1.0f, 1.0f, 1.0f),
	m_Camera(Gameobject::FindComponent<Camera>())
{}

void Shape::SetVertices(const std::vector<Vector2>& verts)
{
	m_Vertices = verts;
	UpdateMesh();
}

void Shape::UpdateMesh()
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

void Shape::OnUpdate()
{
	m_Shader.Bind();

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(-gameobject->transform.position.x * SCALE, gameobject->transform.position.y * SCALE, 1));
	model = glm::rotate(model, gameobject->transform.rotation, glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(gameobject->transform.scale.x * SCALE, gameobject->transform.scale.y * SCALE, 1));

	m_Shader.SetUniform<glm::mat4>("model", model);
	m_Shader.SetUniform<glm::vec4>("color", glm::vec4(m_Color.r, m_Color.g, m_Color.b, m_Color.a));
	m_Shader.SetUniform<glm::mat4>("projection", m_Camera->GetProjection());
	m_Shader.SetUniform<glm::mat4>("view", m_Camera->CalculateViewMatrix());

	m_Mesh.Draw();

	Shader::Unbind();
}