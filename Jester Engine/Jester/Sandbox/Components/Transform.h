#pragma once

#include "../Components.h"

struct TransformData
{
	TransformData()
		: position(0, 0), scale(1, 1), rotation(0)
	{}

	Vector2 position;
	Vector2 scale;

	float rotation;
};

class Transform : public Component
{
public:
	void OnAwake() override
	{
		std::cout << "Transform Awake\n";
		std::cout << transform.position << "\n";
	}
	void OnFixedUpdate(const Time* Time) override
	{
		std::cout << "transform\n";
	}

	TransformData transform;
	//data regarding children/parents
};

