#pragma once

#include <string>

#include "../Core/Color.h"
#include "../Core/Vector2.h"
#include "../Core/Vector3.h"
#include "../Core/Window.h"

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

#include "Renderer.h"

enum class SortingLayer
{
	Default   = -1,
	Background = 0,
	Forground  = 1,
	UI         = 2,
};

class Sprite : public Component
{

	friend Renderer;

public:
	Sprite();

	const char* GetName() override { return "Sprite"; }
	void OnUpdate() override;
	void OnGuiUpdate() override;
	inline void SetTexture(const std::string& path) { m_Texture.SetTexture(path); }

	Color color;
	SortingLayer sortingLayer;
	int orderInLayer;

private:
	Mesh m_Mesh;
	Shader m_Shader;
	Texture m_Texture;

	Camera* m_Camera;
};

