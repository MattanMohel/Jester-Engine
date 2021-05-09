#pragma once

#include "../Jester.h"

class SampleComponent : public Component
{
public:
	const char* GetName() override { return "Sample"; }
	void OnAwake() override;
	void OnUpdate() override;
	void OnGuiUpdate() override;

	bool move = false;

	Camera* cam;
};

