#pragma once

#include <vector>

#include "Vector2.h"
#include "Vector3.h"

#include "Component.h"
#include "Gameobject.h"

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
	const std::vector<Vector2>& GetIndices() const;
	Vector2 GetIndex(int index) const;

	bool isTrigger() const;
	bool isPhysics() const;

	Type GetType() const;

	inline bool isInCollisionArray(const Collider* a) const;
	inline auto&& collisionArrayIt(const Collider* a) const;

	void OnUpdate(const Time* Time) override;

private:
	static void CheckCollisions();
	static bool isColliding(const Collider* a, const Collider* b);	

	Type m_Type = Type::Polygon;
	State m_State = State::Physics;

	std::vector<Vector2> Indices;
	std::vector<Collider*> Collisions;

	static std::vector<Collider*> colliderRegistery;
	static bool checked;
};

