#include "Sprite.h"

#include "RendererBase.h"

#include "../User Interface/UI.h"
#include "../Core/Gameobject.h"
#include "../Core/Component.h"
#include "../Core/Time.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Sprite::Sprite()
	: m_Shader(VS_PATH, FS_PATH),
	m_Mesh(RenderMode::TRIANGLES), m_Color(1.0f, 1.0f, 1.0f, 1.0f), 
	m_Camera(Gameobject::FindComponent<Camera>())
{
	m_Mesh.CreateMesh(VERTICES, INDICES, 20, 12);
	m_Texture.LoadTexture();
}

void Sprite::OnUpdate() 
{
	m_Shader.Bind();
	m_Texture.Bind();

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(-gameobject->transform.position.x * SCALE, gameobject->transform.position.y * SCALE, 1));
	model = glm::rotate(model, gameobject->transform.rotation * Deg2Rad, glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(gameobject->transform.scale.x * SCALE, gameobject->transform.scale.y * SCALE, 1));

	m_Shader.SetUniform<glm::mat4>("model", model);
	m_Shader.SetUniform<glm::vec4>("color", glm::vec4(m_Color.r, m_Color.g, m_Color.b, m_Color.a));
	m_Shader.SetUniform<glm::mat4>("projection", m_Camera->Projection());
	m_Shader.SetUniform<glm::mat4>("view", m_Camera->CalculateViewMatrix());

	m_Mesh.Draw();

	Texture::Unbind();
	Shader::Unbind();
}

void Sprite::OnGuiUpdate()
{
	Jester::UI::Serialize("Color", m_Color);
}

