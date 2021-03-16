#pragma once

#include "../Components.h"

class Sample : public Component
{
public:
	void OnAwake() override 
	{
		Logger::Print("Sample: Awake");
	}
	void OnUpdate(const Time* Time) override
	{
		
	}
	void OnFixedUpdate(const Time* Time) override
	{
		Logger::Print("Sample: Fixed Update");
	}
};

