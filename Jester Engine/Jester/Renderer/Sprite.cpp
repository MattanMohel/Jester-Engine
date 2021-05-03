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
	sortingLayer(SortingLayer::Default), orderInLayer(0), m_Camera(Gameobject::FindComponent<Camera>())
{
	m_Mesh.CreateMesh(VERTICES, INDICES, 20, 6);
}

void Sprite::OnUpdate() 
{
	Renderer::AddSprite(this);
	m_Shader.Bind();
	m_Texture.Bind(0);

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(-gameobject->transform.position.x * SCALE, gameobject->transform.position.y * SCALE, 1));
	model = glm::rotate(model, gameobject->transform.rotation * Deg2Rad, glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(gameobject->transform.scale.x * SCALE, gameobject->transform.scale.y * SCALE, 1));

	m_Shader.SetUniform<glm::mat4>("model", model); 
	//m_Shader.SetUniform<glm::vec4>("color", glm::vec4(color.r, color.g, color.b, color.a));
	m_Shader.SetUniform<glm::mat4>("projection", m_Camera->GetProjection());
	m_Shader.SetUniform<glm::mat4>("view", m_Camera->CalculateViewMatrix());

	m_Mesh.Draw();

	Texture::Unbind(0);
	Shader::Unbind();
}

void Sprite::OnGuiUpdate()
{
	Jester::UI::Serialize("Color", color);
}

