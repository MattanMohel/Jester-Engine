#pragma once

#include <vector>
#include "Camera.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "RendererBase.h"

#include "../Core/Vector2.h"
#include "../Core/Component.h"
#include "../Core/Color.h"

class Shape : public Component
{
public:
	Shape();

	const char* GetName() override { return "Shape"; }
	void OnUpdate() override;

	template<typename... Vertices>
	void SetVertices(Vertices... vertices)
	{
		(m_Vertices.push_back(std::forward<Vector2>(vertices)), ...);
		UpdateMesh();
	}

	void SetVertices(const std::vector<Vector2>& verts);
	void UpdateMesh();

	inline Color& color() { return m_Color; }

private:
	std::vector<Vector2> m_Vertices;

	Mesh m_Mesh;
	Shader m_Shader;

	Color m_Color;

	Camera* m_Camera;
};