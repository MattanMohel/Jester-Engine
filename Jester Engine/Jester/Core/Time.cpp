#include "Time.h"

float Time::deltaTime;
float Time::previousTime = 0.0f;
long double Time::timeSinceInit = 0.0f;

void Time::Init()
{
	deltaTime = Window::Get()->GetTime();
	previousTime = Window::Get()->GetTime(); 
}

void Time::OnUpdate()
{
	float currTime = Window::Get()->GetTime();
	deltaTime = currTime - previousTime;
	previousTime = currTime;

	timeSinceInit += deltaTime;
}
