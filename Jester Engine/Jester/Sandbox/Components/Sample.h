#pragma once

#include "../Components.h"

class Sample : public Component
{
public:
	void OnAwake() override 
	{
		std::cout << "Sample Component: Awake\n";
	}
	void OnUpdate(const Time* Time) override
	{

	}
	void OnFixedUpdate(const Time* Time) override
	{
		PrintSample(3);
	}

	void PrintSample(int a)
	{
		std::cout << "sample printed: " << a << "\n";
	}
};

