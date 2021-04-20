#pragma once

#include "Renderer/Window.h"
#include <cmath>

class Application;

class Time
{

#define MIL 1000.0f

	friend class Application;

public:
	void OnUpdate();

	inline float DeltaTime() const { return m_DeltaTime; }
	inline float TimeSinceStartupInSeconds() const { return m_TimeSinceInit - glfwGetTime(); }
	inline float TimeSinceStartupInMilliseconds() const { return (m_TimeSinceInit - glfwGetTime()) / MIL; }

	double GetFPS() const { return round(1 / m_DeltaTime); }

private:
	static Time* Get();

	Time();
	~Time() { delete Get(); }

	float m_DeltaTime, m_PreviousTime;
	long double m_TimeSinceInit;
}; 