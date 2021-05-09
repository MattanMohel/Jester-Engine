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
	m_Mesh(RenderMode::TRIANGLES), color(1.0f, 1.0f, 1.0f, 1.0f), 
	sortingLayer(SortingLayer::Default), orderInLayer(0), m_Camera(Object::FindComponent<Camera>())
{
	m_Mesh.CreateMesh(VERTICES, (unsigned int*)INDICES, 20, 12);
}

void Sprite::OnUpdate() 
{
	m_Shader.Bind();
	m_Texture.Bind();

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(-object->transform.position.x * SCALE, object->transform.position.y * SCALE, 1));
	model = glm::rotate(model, object->transform.rotation * Deg2Rad, glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(object->transform.scale.x * SCALE, object->transform.scale.y * SCALE, 1));
	// projection * view * model * vec4(pos, 1.0f);

	glm::vec4 pos = m_Camera->Projection() * m_Camera->CalculateViewMatrix() * model * glm::vec4(1, 1, 1, 1);

	m_Shader.SetUniform<glm::mat4>("model", model); 
	m_Shader.SetUniform<glm::vec4>("color", glm::vec4(color.r, color.g, color.b, color.a));
	m_Shader.SetUniform<glm::mat4>("projection", m_Camera->Projection());
	m_Shader.SetUniform<glm::mat4>("view", m_Camera->CalculateViewMatrix());

	m_Mesh.Draw();

	Texture::Unbind();
	Shader::Unbind();
}

void Sprite::OnGuiUpdate()
{
	Jester::UI::Serialize("Color", color);
}

