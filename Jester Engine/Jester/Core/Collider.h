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
	const char* GetName() override{ return "Collider"; }
	void OnAwake() override; 
	void OnDestroy() override;
	void OnUpdate() override;
	void OnGuiUpdate() override;
	// Set vertices via variadic template
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
	// Set vertices via existing vector
	void SetVertices(const std::vector<Vector2>&);
	// Set a vertex at a given index
	void SetVertex(Vector2&, size_t);
	// Remove a vertex at a given index
	void RemoveVertex(size_t);
	// Add vertex at a given index
	void AddVertex(size_t);
	// Returns the normal between two given indices
	Vector2 GetSegmentNormal(size_t, size_t) const;
	// Returns a vector of all indices
	const std::vector<Vector2>& GetVertices() const;
	// Returns a given index 
	Vector2 GetIndex(int) const;

	bool isTrigger() const;
	bool isPhysics() const;

	Type GetType() const;

	inline bool isInCollisionArray(const Collider*) const;

private:
	void RefreshVertices();
	static void CheckCollisions();
	static bool isColliding(const Collider*, const Collider*, Vector2&, Vector2&);	

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

