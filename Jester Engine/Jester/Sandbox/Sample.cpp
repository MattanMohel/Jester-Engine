#include "Sample.h"

class Time;

void SampleComponent::OnAwake()
{
	Logger::Print("Sample: Awake");
}

void SampleComponent::OnUpdate(const Time* Time)
{
	std::cout << Time->DeltaTime() << '\n';
}
