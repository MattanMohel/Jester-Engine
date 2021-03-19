#include "Sample.h"

class Time;

void Sample::OnAwake()
{
	Logger::Print("Sample: Awake");
}

void Sample::OnFixedUpdate(const Time* Time)
{
	Logger::Print(gameobject->name, "'s Sample printed from fixed update");
}
