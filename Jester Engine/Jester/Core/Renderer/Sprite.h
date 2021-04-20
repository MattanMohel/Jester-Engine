#pragma once

#include <string>

#include "../Color.h"
#include "../Vector2.h"
#include "../Vector3.h"

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Window.h"

#define SCALE 500.0f

class Sprite : public Component
{
public:
	Sprite();

	void OnUpdate(const Time* time) override;

	Color& Colors() { return m_Color; }

	inline void SetTexture(const std::string& path) { m_Texture.SetTexture(path); }

private:
	Mesh m_Mesh;
	Shader m_Shader;
	Texture m_Texture;

	Color m_Color;

	Camera* m_Camera;
};

