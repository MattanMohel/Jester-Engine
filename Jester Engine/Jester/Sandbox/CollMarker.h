#pragma once

#include "Internal.h"

class CollMarker : public Component
{
public:
	void OnUpdate();
	void OnGuiUpdate();

	void OnCollisionEnter(Collider& other) override;
	void OnCollisionExit(Collider& other) override;

	float rotSpeed = 0.02f;
};

