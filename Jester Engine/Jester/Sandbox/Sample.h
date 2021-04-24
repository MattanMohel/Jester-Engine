#pragma once

#include "Internal.h"

class SampleComponent : public Component
{
public:
	void OnAwake() override;
	void OnUpdate() override;


	bool move = false;

	Camera* cam;
};

