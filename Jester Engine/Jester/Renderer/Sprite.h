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

class Sprite : public Component
{
public:
	Sprite();

	const char* GetName() override { return "Sprite"; }
	void OnUpdate() override;
	void OnGuiUpdate() override;

	Color& color() { return m_Color; }

	inline void SetTexture(const std::string& path) { m_Texture.SetTexture(path); }

private:
	Mesh m_Mesh;
	Shader m_Shader;
	Texture m_Texture;

	Color m_Color;

	Camera* m_Camera;
};

