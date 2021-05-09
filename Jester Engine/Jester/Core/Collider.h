#pragma once

#include <vector>
#include "Vector2.h"
#include"../Renderer/Line.h"

#define CALC_PRECISION 0.0f
#define COLLIDER_COLOR 70.0f/255.0f, 236.0f/255.0f, 86.0f/255.0f, 1.0f

class Collider : public Component
{

enum class Type
{
	Polygon, Box, Circle, Capsule
};

enum class State
{
	Trigger, Physics
};

public:
	Collider();
	~Collider();

	const char* GetName() override{ return "Collider"; }
	void OnAwake() override; 
	void OnUpdate() override;
	void OnGuiUpdate() override;

	template<typename... Vertices>
	void SetVertices(Vertices... vertices)
	{
		(m_Vertices.push_back(std::forward<Vector2>(vertices)), ...); 

		float maxDistance = 0;
		for (const auto& vert : m_Vertices)
		{
			float distance = Vector2::SquaredDistance(vert, Vector2::Zero);
			maxDistance = distance > maxDistance? distance : maxDistance;  
		}

		m_FurthestVertexDistance = maxDistance;

		m_LineVisual.SetVertices(m_Vertices);
	}
	void SetVertices(const std::vector<Vector2>& verts);
	void SetVertex(Vector2& newVertex, size_t index);

	void RemoveVertex(size_t index);
	void AddVertex(size_t index);

	void RefreshVertices();

	const std::vector<Vector2>& GetVertices() const;
	Vector2 GetIndex(int index) const;

	bool isTrigger() const;
	bool isPhysics() const;

	Type GetType() const;

	inline bool isInCollisionArray(const Collider* a) const;

private:
	static void CheckCollisions();
	static bool isColliding(const Collider* a, const Collider* b);	

	Type m_Type = Type::Polygon;
	State m_State = State::Physics;

	Line m_LineVisual; 

	std::vector<Vector2> m_Vertices;
	std::vector<Collider*> m_Collisions;

	float m_FurthestVertexDistance; 

	static std::vector<Collider*> colliderRegistery;
	static size_t callIndex;
	static bool checked;
};

