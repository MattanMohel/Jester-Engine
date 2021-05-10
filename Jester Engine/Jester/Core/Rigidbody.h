#pragma once

#include <vector>
#include "Component.h"
#include "Vector2.h"

class Collider;

class Rigidbody : public Component
{
public:
	void OnGuiUpdate() override;
	void OnAwake() override;
	void OnDestroy() override;

	void OnCollisionStay(Collider&, Vector2) override;
	Vector2 GetVelocityMultiplier() const { return m_Multiplier; }
	static const std::vector<Rigidbody*>& GetRigidbodies() { return rigidbodyRegistery; }

	float friction = 0;
	Vector2 velocity = Vector2(0, 0);

private:
	Vector2 m_Multiplier = Vector2(1, 1);
	static std::vector<Rigidbody*> rigidbodyRegistery;
};

