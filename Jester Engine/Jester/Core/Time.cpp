#include "Time.h"

void Time::OnUpdate()
{
	float currTime = Window::Get()->GetTime();
	m_DeltaTime = currTime - m_PreviousTime;
	m_PreviousTime = currTime;

	m_TimeSinceInit += m_DeltaTime;
}

Time* Time::Get()
{
	static Time* s_Instance = new Time();
	return s_Instance;
}

Time::Time()
	: m_DeltaTime(Window::Get()->GetTime()), 
	m_PreviousTime(Window::Get()->GetTime()), 
	m_TimeSinceInit(0.0f)
{}