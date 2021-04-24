#pragma once

#include <glm/glm.hpp>
#include <vector>

#include"../Renderer/Line.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Component.h"
#include "Gameobject.h"

#define CALC_PRECISION 0.005f
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

	const std::vector<Vector2>& GetVertices() const;
	Vector2 GetIndex(int index) const;

	bool isTrigger() const;
	bool isPhysics() const;

	Type GetType() const;

	inline bool isInCollisionArray(const Collider* a) const;

	void OnAwake() override;
	void OnUpdate() override;

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

