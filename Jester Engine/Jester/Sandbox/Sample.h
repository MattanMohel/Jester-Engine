#pragma once

#include "../Jester.h"

class SampleComponent : public Component
{
public:
	const char* GetName() override { return "Sample"; }
	void OnAwake() override;
	void OnUpdate() override;
	void OnGuiUpdate() override;

	void OnCollisionStay(Collider&, Vector2) override;
	void OnCollisionExit(Collider&, Vector2) override;

	float speed = 5;
	bool move = false;
	Rigidbody* rb;
	Camera* cam;
};

