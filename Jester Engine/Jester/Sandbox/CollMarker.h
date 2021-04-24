#pragma once

#include "Internal.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class CollMarker : public Component
{
public:
	void OnUpdate();

	void OnCollisionEnter(Collider& other) override;
	void OnCollisionExit(Collider& other) override;

	std::vector<Gameobject*> points;
};

