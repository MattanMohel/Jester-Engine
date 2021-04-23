#pragma once

#include "Internal.h"

class SampleComponent : public Component
{
public:
	void OnAwake() override;
	void OnUpdate(const Time* Time) override;
	void OnCollisionEnter(Collider& other) override;
	void OnCollisionExit(Collider& other) override; 

	bool move = false;

	std::vector<Gameobject*> points;
};

