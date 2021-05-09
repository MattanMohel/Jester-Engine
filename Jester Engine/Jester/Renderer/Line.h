#pragma once

#include <vector>
#include "Mesh.h"
#include "Shader.h"
#include "../Core/Vector2.h"
#include "../Core/Component.h"
#include "../Core/Color.h"

class Camera;

class Line : public Component 
{
public:
	Line();

	const char* GetName() override { return "Line"; }
	void OnUpdate() override;

	template<typename... Vertices>
	void SetVertices(Vertices... vertices) 
	{
		(m_Vertices.push_back(std::forward<Vector2>(vertices)), ...);
		UpdateMesh();
	}

	void SetVertices(const std::vector<Vector2>&);
	void SetVertex(const Vector2&, size_t); 

	void RemoveVertex(size_t);
	void AddVertex(size_t);

	void UpdateMesh();

	inline Color& color() { return m_Color; }

private:
	std::vector<Vector2> m_Vertices;

	Mesh m_Mesh;
	Shader m_Shader;

	Color m_Color;

	Camera* m_Camera; 
};