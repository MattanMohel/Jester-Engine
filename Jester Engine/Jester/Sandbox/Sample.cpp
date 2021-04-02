#include "Sample.h"

class Time;

void SampleComponent::OnAwake()
{
	Logger::Print("Sample: Awake");
}

void SampleComponent::OnFixedUpdate(const Time* Time)
{
	Logger::Print(gameobject->name, "'s Sample printed from fixed update");
}
