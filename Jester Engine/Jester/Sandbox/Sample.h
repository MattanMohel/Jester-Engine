#pragma once

#include "Internal.h"
#include "../Core/UI.h"

class SampleComponent : public Component
{
public:
	void OnAwake() override;
	void OnUpdate() override;
	void OnGuiUpdate() override;

	bool move = false;

	Camera* cam;
};

