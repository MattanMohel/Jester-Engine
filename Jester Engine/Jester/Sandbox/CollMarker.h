#pragma once

#include "Internal.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class CollMarker : public Component
{
public:
	void OnAwake();
	void OnUpdate(const Time* time);

	std::vector<Gameobject*> points;
};

